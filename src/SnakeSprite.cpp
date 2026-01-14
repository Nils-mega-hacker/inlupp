#include "SnakeSprite.h"
#include "FoodSprite.h"
#include <iostream>

namespace snake{
    int moveCounter = 0;
    int snakeDimensions = 20;
    
    SnakeSprite::SnakeSprite(Engine* eng) : Sprite(400, 300, snakeDimensions, snakeDimensions), engine(eng) {
        direction = Direction::UP;
        size = 2;
        
        body.push_back({400, 300});  
        body.push_back({400, 320});  
    }
    
    void SnakeSprite::tick(){
        moveCounter++;
        if (moveCounter < 5) return;
        moveCounter = 0;
        
        SDL_FPoint newHead = body[0];
        
        switch(direction){
            case Direction::UP:
                newHead.y -= snakeDimensions;
                break;
            case Direction::DOWN:
                newHead.y += snakeDimensions;
                break;
            case Direction::LEFT:
                newHead.x -= snakeDimensions;
                break;
            case Direction::RIGHT:
                newHead.x += snakeDimensions;
                break;
        }
        
        if (newHead.x < 0) {
            newHead.x = cnts::gScreenWidth - snakeDimensions;
        } else if (newHead.x >= cnts::gScreenWidth) {
            newHead.x = 0;
        }
        
        if (newHead.y < 0) {
            newHead.y = cnts::gScreenHeight - snakeDimensions;
        } else if (newHead.y >= cnts::gScreenHeight) {
            newHead.y = 0;
        }
        
        for (size_t i = 0; i < body.size(); i++) {
            if (newHead.x == body[i].x && newHead.y == body[i].y) {
                engine->gameOver();
                return;
            }
        }
        
        body.insert(body.begin(), newHead);
        
        if (body.size() > size) {
            body.pop_back();
        }
        
        SDL_FRect& r = const_cast<SDL_FRect&>(getRect());
        r.x = body[0].x;
        r.y = body[0].y;
    }

    void SnakeSprite::onCollisionWith(SpritePtr other){
        if (dynamic_cast<FoodSprite*>(other.get())) {
            size += 1;
            int random = rand() % 8 + 1;
            std::string soundName = "eat" + std::to_string(random);
            engine->playLoadedSound(soundName);
        } else {
            engine->gameOver();
        }
    }

    void SnakeSprite::onButtonDown(const SDL_Event& event){
        if(event.type == SDL_EVENT_KEY_DOWN){
            switch(event.key.key){
                case SDLK_UP:
                    if(direction == Direction::DOWN){
                        break;
                    }
                    direction = Direction::UP;
                    break;
                case SDLK_DOWN:
                    if(direction == Direction::UP){
                        break;
                    }
                    direction = Direction::DOWN;
                    break;
                case SDLK_LEFT:
                    if(direction == Direction::RIGHT){
                        break;
                    }
                    direction = Direction::LEFT;
                    break;
                case SDLK_RIGHT:
                    if(direction == Direction::LEFT){
                        break;
                    }
                    direction = Direction::RIGHT;
                    break;
            }
        }
    }

    void SnakeSprite::draw() const {
        SDL_SetRenderDrawColor(engine->getRen(), 0, 255, 0, 255);
        
        for (const SDL_FPoint& segment : body) {
            SDL_FRect segmentRect = {segment.x, segment.y, snakeDimensions, snakeDimensions};
            SDL_RenderFillRect(engine->getRen(), &segmentRect);
        }
    }
}

