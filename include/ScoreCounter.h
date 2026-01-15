#pragma once
#include "Sprite.h"
#include <SDL3_ttf/SDL_ttf.h>


class ScoreCounter {
    public:
    ScoreCounter(SDL_Renderer* renderer, TTF_Font* font);
    void render();


    private:
    int score;
    void updateTexture();
    void increase();

    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* texture;
    SDL_FRect rect;

};