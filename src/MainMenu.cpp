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

    MenuResult MainMenu::run(){
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
                        return MenuResult::Quit;
                        break;

                    case SDL_EVENT_KEY_DOWN:
                        if(event.key.key == SDLK_RETURN){
                            return MenuResult::Play;
                        }
                        break;

                    case SDL_EVENT_MOUSE_BUTTON_DOWN:
                        if(event.button.button == SDL_BUTTON_LEFT){
                            float mx = event.button.x;
                            float my = event.button.y;
                            if(mx >= btnRect.x && mx <= btnRect.x + btnRect.w &&
                            my >= btnRect.y && my <= btnRect.y + btnRect.h){
                                return MenuResult::Play;
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


            // Rita high score text
             TTF_Font* smallFont = TTF_OpenFont(constants::font_str.c_str(), 32);
            if(!font){
                std::cerr << "TTF_OpenFont failed: " << std::endl;
            }

            std::string hsText = "HIGH SCORE: " + std::to_string(highScore);

            SDL_Color hsColor = {200, 200, 200, 255};

            SDL_Surface* hsSurf =
                TTF_RenderText_Solid(smallFont, hsText.c_str(), hsText.length(), hsColor);

            SDL_Texture* hsTex = SDL_CreateTextureFromSurface(ren, hsSurf);
            SDL_DestroySurface(hsSurf);

            float hsW, hsH;
            SDL_GetTextureSize(hsTex, &hsW, &hsH);

            SDL_FRect hsRect = {
                constants::gScreenWidth / 2 - hsW / 2,
                20,   // vertical position under title
                hsW,
                hsH
            };

       if (lastGameWasHighScore) {
            std::string msg = "NEW HIGH SCORE!";
            SDL_Color gold = {255, 215, 0, 255};

            SDL_Surface* msgSurf =
                TTF_RenderText_Solid(smallFont, msg.c_str(), msg.length(), gold);

            SDL_Texture* msgTex = SDL_CreateTextureFromSurface(ren, msgSurf);
            SDL_DestroySurface(msgSurf);

            float mw, mh;
            SDL_GetTextureSize(msgTex, &mw, &mh);

            SDL_FRect msgRect = {
                constants::gScreenWidth / 2 - mw / 2,
                60,
                mw,
                mh
            };

            SDL_RenderTexture(ren, msgTex, nullptr, &msgRect);
            SDL_DestroyTexture(msgTex);
        }



            SDL_RenderTexture(ren, hsTex, nullptr, &hsRect);
            SDL_DestroyTexture(hsTex);


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

        return MenuResult::Quit;
    }


    void MainMenu::setHighScore(int score) {
        highScore = score;
    }

    void MainMenu::setLastGameWasHighScore(bool b) {
        lastGameWasHighScore = b;
    }


}