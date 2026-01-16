#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include <vector>
#include <memory>
#include <map>
#include <iostream>

#include "Constants.h"
#include "Sprite.h"
#include "ScoreCounter.h"

namespace cnts = constants;

namespace snake{
    class Sprite;
    typedef std::shared_ptr<Sprite> SpritePtr;

    class Engine{
    public:
        Engine();
        ~Engine();
        SDL_Renderer* getRen() const { return ren; }
        SDL_Window* getWin() const { return win; }
        void add(SpritePtr spr);
        void remove(SpritePtr spr);
        void run();
        void reset();
        void gameOver();
        void addScore();
        int getScore();

        //ljudeffekter
        void loadSound(const std::string& name, const std::string& soundFile);
        void playLoadedSound(const std::string& name);
        void setSoundVolume(const std::string& name, float volume);
   
        // Bakgrundsmusik
        void updateAudio();
        void loadBackgroundMusic(const std::string& musicFile);
        void playBackgroundMusic(bool loop = true);
        void pauseBackgroundMusic();
        void resumeBackgroundMusic();
        void setMusicVolume(float volume); // 0.0 - 1.0

    private:
        bool running = false;
        bool paused = false;
        SDL_Window* win;
        SDL_Renderer* ren;
        std::vector<SpritePtr> sprites, added, removed;
        // Ljudeffekter
        std::map<std::string, SDL_AudioSpec> audioSpecs;
        std::map<std::string, Uint8*> audioBuffers;
        std::map<std::string, Uint32> audioLengths;
        SDL_AudioStream* soundStream;

        // Bakgrundsmusik
        SDL_AudioSpec bgMusicSpec;
        Uint8* bgMusicBuffer;
        Uint32 bgMusicLength;
        SDL_AudioStream* bgMusicStream;
        bool musicLooping;
        
        std::unique_ptr<ScoreCounter> scoreCounter;  
        
    };
    extern Engine eng;
}