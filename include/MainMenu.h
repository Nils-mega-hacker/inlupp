#include "Engine.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace snake{
    class MainMenu{
        public:
            MainMenu(Engine* eng);
            ~MainMenu();
            void run();
        private:
            Engine* engine;
            void draw();
            void handleEvents();
            SDL_Window* win;
            SDL_Renderer* ren;
            SDL_FRect rect;
            std::string txt;
            TTF_Font* font;
    };
}