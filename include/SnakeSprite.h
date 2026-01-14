#pragma once
#include "Sprite.h"
#include "Constants.h"
#include "Direction.h"
#include "Engine.h"

namespace snake{
    class SnakeSprite : public Sprite{
    public:
        SnakeSprite(Engine* eng);
        void onButtonDown(const SDL_Event& event); 
        const std::vector<SDL_FPoint>& getBody() const { return body; }      

        void tick();
        void onCollisionWith(SpritePtr other);
        void draw() const; // Inte virtual


        SnakeSprite(const Sprite& other) = delete;
        const SnakeSprite& operator=(const Sprite& other) = delete;

    protected:

    private:
        Direction direction;
        int size;
        Engine* engine;
        std::vector<SDL_FPoint> body;  // Add this - stores each segment position

    };
}