#include "FoodSprite.h"
#include "Engine.h"
#include <iostream>

namespace snake{
    FoodSprite::FoodSprite() : Sprite(50, 50, 30, 30) {  // Make it 30x30 pixels
        xc = 50;
        yc = 50;
    }

    FoodSprite::FoodSprite(float x, float y) : Sprite(x, y, 30, 30), xc(x), yc(y) {}  
    
    void FoodSprite::draw() const{
        const SDL_FRect& r = getRect();
        SDL_SetRenderDrawColor(eng.getRen(), 255, 0, 0, 255);
        if (!SDL_RenderFillRect(eng.getRen(), &r)) {
            std::cerr << "Food render failed: " << SDL_GetError() << std::endl;
    }
}

    void FoodSprite::onCollisionWith(SpritePtr other){
        float newX = rand() % (cnts::gScreenWidth - 30);
        float newY = rand() % (cnts::gScreenHeight - 30);
        
        SDL_FRect& r = const_cast<SDL_FRect&>(getRect());
        r.x = newX;
        r.y = newY;
        
        xc = newX;
        yc = newY;
    }
    void FoodSprite::tick() {}
}
