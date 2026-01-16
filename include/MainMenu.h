#include "Engine.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace snake{
    enum class MenuResult {
        Play,
        Quit
    };


    class MainMenu{
        public:
            MainMenu(Engine* eng);
            ~MainMenu();
            MenuResult run();
            void setHighScore(int score);
            void setLastGameWasHighScore(bool b);
        private:
            Engine* engine;
            void draw();
            void handleEvents();
            SDL_Window* win;
            SDL_Renderer* ren;
            SDL_FRect rect;
            std::string txt;
            TTF_Font* font;
            int highScore = 0;
            bool lastGameWasHighScore = false;
    };
}