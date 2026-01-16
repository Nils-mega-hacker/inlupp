#pragma once
#include "Direction.h"
#include "Engine.h"
#include "FoodSprite.h"

//spelklass
namespace snake{
    class SnakeSprite : public Sprite{
    public:
        SnakeSprite(Engine* eng);
        void onButtonDown(const SDL_Event& event); 
        const std::vector<SDL_FPoint>& getBody() const { return body; }      

        void tick();
        void onCollisionWith(SpritePtr other);
        void draw() const; 

        SnakeSprite(const Sprite& other) = delete;
        const SnakeSprite& operator=(const Sprite& other) = delete;

    protected:

    private:
        Direction direction;
        int size;
        Engine* engine;
        std::vector<SDL_FPoint> body;  
    };
}