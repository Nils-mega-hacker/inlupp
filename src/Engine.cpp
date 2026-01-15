#include "Engine.h"
#include "Sprite.h"
#include "ScoreCounter.h"
#include <iostream>


namespace snake{
    
    bool running = true;

    Engine::Engine(){
            std::cout << "Creating Engine..." << std::endl;
            win = SDL_CreateWindow("Snake", cnts::gScreenWidth, cnts::gScreenHeight,0);
            ren = SDL_CreateRenderer(win, NULL);
            srand(time(NULL));
            std::cout << "Engine created. Window: " << win << ", Renderer: " << ren << std::endl;
    }

    Engine::~Engine(){
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

    void Engine::run(){
        const int FPS = 60; // Frames Per Second
        const int TICKINTERVAL = 1000 / FPS; // In miliseconds
        
        TTF_Init(); //Initialize TTf
        TTF_Font* font = TTF_OpenFont("resources/fonts/Outfit-VariableFont_wght.ttf", 24); //Ska vara konstant var?
        scoreCounter = std::make_unique<ScoreCounter>(ren, font);


        if(!font) {
            std::cerr << SDL_GetError() << std::endl;
        }

        std::cout << "Starting run() - sprites.size(): " << sprites.size() << ", added.size(): " << added.size() << std::endl;

        running = true;
        int frameCount = 0;
        while (running){
            Uint64 nextTick = SDL_GetTicks() + TICKINTERVAL; 
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_EVENT_QUIT:
                        running = false; 
                        break;
                    case SDL_EVENT_KEY_DOWN:
                        for(SpritePtr spr : sprites)
                            spr->onButtonDown(event);
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

            Sint64 delay = nextTick - SDL_GetTicks();
            if (delay > 0)
                SDL_Delay(delay); 
        } // while running
    } // run

    Engine eng;
}