#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>
#include "Constants.h"

class ScoreCounter {
public:
    ScoreCounter(SDL_Renderer* renderer, TTF_Font* font);
    void render() const;
    void increase();
    void reset();
    int getScore() const;

private:
    int score;
    void updateTexture();
    
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* texture;
    SDL_FRect rect;
};