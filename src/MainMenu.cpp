#include "MainMenu.h"
#include <iostream>

namespace snake{
    MainMenu::MainMenu(Engine* eng) : engine(eng){
        eng->loadBackgroundMusic(constants::mainMenu_str);
        eng->setMusicVolume(0.3f);
        eng->playBackgroundMusic(true);

        ren = engine->getRen();

        // Ladda font
        font = TTF_OpenFont(constants::font_str.c_str(), 96);
        if(!font){
            std::cerr << "TTF_OpenFont failed: " << std::endl;
        }

        txt = "PLAY";
    }

    MainMenu::~MainMenu(){
        if(font) TTF_CloseFont(font);
    }

    void MainMenu::run(){
        bool running = true;
        bool isHovering = false;
        
        SDL_FRect btnRect = { constants::gScreenWidth/2 - 200, 
                             constants::gScreenHeight/2 + 50,
                             400, 150 }; 

        SDL_FRect snakeRect = { constants::gScreenWidth/2 - 150,
                               constants::gScreenHeight/2 - 50,
                               200, 40 };
        
        SDL_FRect foodRect = { constants::gScreenWidth/2 + 110,
                              constants::gScreenHeight/2 - 45,
                              30, 30 };

        while(running){
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_EVENT_QUIT:
                        exit(0);
                        break;

                    case SDL_EVENT_KEY_DOWN:
                        if(event.key.key == SDLK_RETURN){
                            running = false;
                        }
                        break;

                    case SDL_EVENT_MOUSE_BUTTON_DOWN:
                        if(event.button.button == SDL_BUTTON_LEFT){
                            float mx = event.button.x;
                            float my = event.button.y;
                            if(mx >= btnRect.x && mx <= btnRect.x + btnRect.w &&
                            my >= btnRect.y && my <= btnRect.y + btnRect.h){
                                running = false;
                            }
                        }
                        break;

                    case SDL_EVENT_MOUSE_MOTION:
                        {
                            float mx = event.motion.x;
                            float my = event.motion.y;
                            isHovering = (mx >= btnRect.x && mx <= btnRect.x + btnRect.w &&
                                         my >= btnRect.y && my <= btnRect.y + btnRect.h);
                        }
                        break;
                }
            }

            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);

            SDL_Surface* titleSurf = TTF_RenderText_Solid(font, "SNAKE", 0, {255, 255, 255});
            SDL_Texture* titleTex = SDL_CreateTextureFromSurface(ren, titleSurf);
            SDL_DestroySurface(titleSurf);

            float titleW, titleH;
            SDL_GetTextureSize(titleTex, &titleW, &titleH);
            SDL_FRect titleRect = { constants::gScreenWidth/2 - titleW/2,
                                   80,  
                                   titleW, titleH };
            SDL_RenderTexture(ren, titleTex, NULL, &titleRect);
            SDL_DestroyTexture(titleTex);

            // Rita orm
            SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
            SDL_RenderFillRect(ren, &snakeRect);

            // Rita mat
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_RenderFillRect(ren, &foodRect);

            // Rita play-knapp
            if(isHovering){
                SDL_SetRenderDrawColor(ren, 180, 220, 180, 255);
            } else {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            }
            SDL_RenderFillRect(ren, &btnRect);

            // Rita "PLAY" text
            SDL_Surface* txtSurf = TTF_RenderText_Solid(font, txt.c_str(), 0, {0,0,0});
            SDL_Texture* txtTex = SDL_CreateTextureFromSurface(ren, txtSurf);
            SDL_DestroySurface(txtSurf);

            float w, h;
            SDL_GetTextureSize(txtTex, &w, &h);
            SDL_FRect txtRect = { constants::gScreenWidth/2 - w/2,
                                constants::gScreenHeight/2 + 132 - h/2,
                                w, h };
            SDL_RenderTexture(ren, txtTex, NULL, &txtRect);
            SDL_DestroyTexture(txtTex);
            
            engine->updateAudio();
            SDL_RenderPresent(ren);
            SDL_Delay(16);
        }
    }
}