#include "Engine.h"
#include "Sprite.h"
#include "ScoreCounter.h"
#include <iostream>


namespace snake{
    
    //bool running = true;

    Engine::Engine(){
        std::cout << "Creating Engine..." << std::endl;
        win = SDL_CreateWindow("Snake", cnts::gScreenWidth, cnts::gScreenHeight,0);
        ren = SDL_CreateRenderer(win, NULL);
        srand(time(NULL));
        
        SDL_Init(SDL_INIT_AUDIO);
        soundStream = nullptr;
        bgMusicStream = nullptr;
        bgMusicBuffer = nullptr;
        musicLooping = false;
        std::cout << "Engine created. Window: " << win << ", Renderer: " << ren << std::endl;
    }

    Engine::~Engine(){
        // Städa ljudeffekter
        for(auto& pair : audioBuffers){
            SDL_free(pair.second);
        }
        if(soundStream) SDL_DestroyAudioStream(soundStream);
        
        // Städa bakgrundsmusik
        if(bgMusicBuffer) SDL_free(bgMusicBuffer);
        if(bgMusicStream) SDL_DestroyAudioStream(bgMusicStream);
        
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
    }

    void Engine::add(SpritePtr spr){
        std::cout << "Adding sprite to 'added' vector" << std::endl;
        added.push_back(spr);
    }

    void Engine::remove(SpritePtr spr){
        removed.push_back(spr);
    }

    //osäkert om detta ska vara i motorn? kanske i main, eller en specifik "snakemotor" (SnakeEngine : public Engine)?
    void Engine::gameOver(){
        running = false;
        std::cout << "Game Over!" << std::endl;
        // ev. visa meny, highscore etc
    }

    //Audio
    void Engine::loadSound(const std::string& name, const std::string& soundFile){
        SDL_AudioSpec spec;
        Uint8* buf;
        Uint32 length;
        
        if(SDL_LoadWAV(soundFile.c_str(), &spec, &buf, &length)){
            audioSpecs[name] = spec;
            audioBuffers[name] = buf;
            audioLengths[name] = length;
            
            if(!soundStream){
                soundStream = SDL_OpenAudioDeviceStream(
                    SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
                SDL_ResumeAudioStreamDevice(soundStream);
            }
        } else {
            std::cerr << "Kunde inte ladda " << soundFile << std::endl;
        }
    }

    void Engine::loadBackgroundMusic(const std::string& musicFile){
        if(bgMusicStream){
            SDL_DestroyAudioStream(bgMusicStream);
            bgMusicStream = nullptr;
        }
        if(bgMusicBuffer){
            SDL_free(bgMusicBuffer);
            bgMusicBuffer = nullptr;
        }

        // ladda ny musik
        if(SDL_LoadWAV(musicFile.c_str(), &bgMusicSpec, &bgMusicBuffer, &bgMusicLength)){
            bgMusicStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                                    &bgMusicSpec, NULL, NULL);
        }
    }

    void Engine::playBackgroundMusic(bool loop){
        if(!bgMusicStream || !bgMusicBuffer) return;
        musicLooping = loop;
        SDL_PutAudioStreamData(bgMusicStream, bgMusicBuffer, bgMusicLength);
        SDL_ResumeAudioStreamDevice(bgMusicStream);
    }

    void Engine::pauseBackgroundMusic(){
        if(bgMusicStream){
            SDL_PauseAudioStreamDevice(bgMusicStream);
        }
    }

    void Engine::resumeBackgroundMusic(){
        if(bgMusicStream){
            SDL_ResumeAudioStreamDevice(bgMusicStream);
        }
    }

    void Engine::setMusicVolume(float volume){
        if(bgMusicStream){
            SDL_SetAudioStreamGain(bgMusicStream, volume);
        }
    }

    void Engine::setSoundVolume(const std::string& name, float volume){
        if(audioBuffers.find(name) != audioBuffers.end() && soundStream){
            SDL_SetAudioStreamGain(soundStream, volume);
        }
    }

    void Engine::playLoadedSound(const std::string& name){
        if(audioBuffers.find(name) != audioBuffers.end()){
            SDL_ClearAudioStream(soundStream);
            SDL_PutAudioStreamData(soundStream, audioBuffers[name], audioLengths[name]);
        }
    }

    void Engine::updateAudio(){
        if(bgMusicStream && musicLooping){
            if(SDL_GetAudioStreamAvailable(bgMusicStream) < bgMusicLength){
                SDL_PutAudioStreamData(bgMusicStream, bgMusicBuffer, bgMusicLength);
            }
        }
    }

    void Engine::run(){
        running = true;
        const int FPS = 60; // Frames Per Second
        const int TICKINTERVAL = 1000 / FPS; // In miliseconds
        
        //TTF_Init(); //Initialize TTF  

        // Ladda font
        TTF_Font* font = TTF_OpenFont(constants::font_str.c_str(), 32);
        if(!font){
            std::cerr << "TTF_OpenFont failed: " << std::endl;
        }

        if(!font) {
            std::cerr << SDL_GetError() << std::endl;
        }

        scoreCounter = std::make_unique<ScoreCounter>(ren, font);

        std::cout << "Starting run() - sprites.size(): " << sprites.size() << ", added.size(): " << added.size() << std::endl;

        running = true;
        int frameCount = 0;
        while (running){
            Uint64 nextTick = SDL_GetTicks() + TICKINTERVAL; 
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_EVENT_QUIT:
                        std::exit(0);
                        break;
                    case SDL_EVENT_KEY_DOWN:
                        if(event.key.key == SDLK_SPACE) {
                            paused = !paused;
                            break;
                        }

                        if(!paused) {
                            for(SpritePtr spr : sprites)
                                spr->onButtonDown(event);
                        }
                        break;
                
                } // switch
            } // while event

            for(SpritePtr spr : added) {
                sprites.push_back(spr);
                if (frameCount == 0) std::cout << "Added sprite to main vector" << std::endl;
            }
            added.clear();

            for(SpritePtr spr : removed){
                for (size_t pos = 0; pos < sprites.size(); pos++){
                    auto iter = sprites.begin() + pos;
                    if(spr == *iter){
                        sprites.erase(iter);
                        break;
                    }
                }            
            }
            removed.clear();

            if (frameCount == 0) {
                std::cout << "Frame 0: sprites.size() = " << sprites.size() << std::endl;
            }

            if(!paused) {
                // Now tick all sprites
                for (SpritePtr spr : sprites)
                    spr->tick();

                // Check collisions
                for(SpritePtr sp1 : sprites){
                    for(SpritePtr sp2 : sprites){
                        if(sp1 != sp2 && sp1->collidedWith(sp2)){
                            sp1->onCollisionWith(sp2);
                            sp2->onCollisionWith(sp1);
                        }
                    }
                }
            }

            // Draw everything
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);
            
            if (frameCount == 0) {
                std::cout << "About to draw " << sprites.size() << " sprites" << std::endl;
            }
            
            for(SpritePtr spr : sprites) {
                if (frameCount == 0) {
                    const SDL_FRect& r = spr->getRect();
                    std::cout << "Drawing sprite at (" << r.x << ", " << r.y << ") size (" << r.w << ", " << r.h << ")" << std::endl;
                }
                spr->draw();
            }

            scoreCounter->render();

            SDL_RenderPresent(ren);

            frameCount++;

            if(bgMusicStream && musicLooping){
                if(SDL_GetAudioStreamAvailable(bgMusicStream) < bgMusicLength){
                    SDL_PutAudioStreamData(bgMusicStream, bgMusicBuffer, bgMusicLength);
                }
            }

            updateAudio();
            Sint64 delay = nextTick - SDL_GetTicks();
            if (delay > 0)
                SDL_Delay(delay); 
        } // while running
    } // run

    void Engine::reset() {
        sprites.clear();
        added.clear();
        removed.clear();


        if(scoreCounter) {
            scoreCounter->reset();
        }

     running = true;
    }

    void Engine::addScore() {
        scoreCounter->increase();
    }
    
    int Engine::getScore() {
        return scoreCounter->getScore();
    }

    Engine eng;
}