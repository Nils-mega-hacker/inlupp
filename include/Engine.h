#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "Constants.h"
#include <map>
#include <SDL3_image/SDL_image.h>
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
        void gameOver();

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
        SDL_Window* win;
        SDL_Renderer* ren;
        std::vector<SpritePtr> sprites, added, removed;
    };
    extern Engine eng;
}
