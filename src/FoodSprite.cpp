#include "FoodSprite.h"
#include "Engine.h"
#include <iostream>
#include "SnakeSprite.h"

namespace snake{

    int foodDimensions = 30; //Daniel

    FoodSprite::FoodSprite() : Sprite(50, 50, foodDimensions, foodDimensions) {  
        xc = 50;
        yc = 50;
    }

    FoodSprite::FoodSprite(float x, float y) : Sprite(x, y, foodDimensions, foodDimensions), xc(x), yc(y) {}  
    
    void FoodSprite::draw() const{
        const SDL_FRect& r = getRect();
        SDL_SetRenderDrawColor(eng.getRen(), 255, 0, 0, 255);
        if (!SDL_RenderFillRect(eng.getRen(), &r)) {
            std::cerr << "Food render failed: " << SDL_GetError() << std::endl;
    }
}

    void FoodSprite::onCollisionWith(SpritePtr other){
        // Get snake body segments
        SnakeSprite* snake = dynamic_cast<SnakeSprite*>(snakePtr.get());
        if (!snake) return;
        
        const std::vector<SDL_FPoint>& body = snake->getBody();  // You'll need to add a getter
        
        bool validPosition = false;
        float newX, newY;
        
        // Keep trying random positions until we find one not on the snake
        while (!validPosition) {
            newX = rand() % (cnts::gScreenWidth - foodDimensions);
            newY = rand() % (cnts::gScreenHeight - foodDimensions);
            
            validPosition = true;
            // Check if position overlaps with any snake segment
            //std::abs = absolutbelopp (bryr  sig inte om det är + eller -)
            for (const SDL_FPoint& segment : body) {
                if (std::abs(newX - segment.x) < 20 && std::abs(newY - segment.y) < 20) {
                    validPosition = false;
                    break;
                }
            }
        }
        
        SDL_FRect& r = const_cast<SDL_FRect&>(getRect());
        r.x = newX;
        r.y = newY;
        xc = newX;
        yc = newY;
    }
    void FoodSprite::tick() {}
}
