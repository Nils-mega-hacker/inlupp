#include "ScoreCounter.h"

ScoreCounter::ScoreCounter(SDL_Renderer* ren, TTF_Font* font) : renderer(ren), font(font), texture(nullptr), score(0) {
    updateTexture();
}

void ScoreCounter::increase() {
    score++;
    updateTexture();
}

void ScoreCounter::reset() {
    score = 0;
    updateTexture();
}

int ScoreCounter::getScore() {
    return score;
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

    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = (constants::gScreenWidth  - rect.w) / 2.0f;
    rect.y = 20;
    
    SDL_DestroySurface(surface);
}

void ScoreCounter::render() {
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}