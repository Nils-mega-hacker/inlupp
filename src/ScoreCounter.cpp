#include "ScoreCounter.h"
#include <iostream>


ScoreCounter::ScoreCounter(SDL_Renderer* ren, TTF_Font* font) : renderer(ren), font(font), texture(nullptr), score(0) {
    updateTexture();
}

void ScoreCounter::increase() {
    score++;
    updateTexture();
}


void ScoreCounter::updateTexture() {
    if(texture) {
        SDL_DestroyTexture(texture);
    }

    SDL_Color white = {255, 255, 255, 255};

    std::string text = "Score: " + std::to_string(score);

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), white);

    if (!surface) {
    std::cout << "Text surface failed: " << SDL_GetError() << std::endl;
    return;
}


    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) {
    std::cout << "Texture creation failed: " << SDL_GetError() << std::endl;
}

    rect.x = 10;
    rect.y = 10;
    rect.w = surface->w;
    rect.h = surface->h;
    
    SDL_DestroySurface(surface);
}

void ScoreCounter::render() {
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}