#pragma once
#include "Sprite.h"

namespace snake{
    class FoodSprite : public Sprite{

    public:
        ~FoodSprite()=default;
        FoodSprite();
        FoodSprite(float x,float y);
        void draw() const;
        void tick();
        void setSnake(SpritePtr snake) { snakePtr = snake; }
        void onButtonDown(const SDL_Event& event){}
        void onCollisionWith(SpritePtr other);

    private:
        float xc;
        float yc;
        SpritePtr snakePtr;
    };
}