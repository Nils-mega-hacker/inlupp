#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>
#include "Constants.h"

// TA BORT: #include "Engine.h"

class ScoreCounter {
public:
    ScoreCounter(SDL_Renderer* renderer, TTF_Font* font);
    void render();
    void increase();
    void reset();
    int getScore();

private:
    int score;
    void updateTexture();
    
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* texture;
    SDL_FRect rect;
};