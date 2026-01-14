#include "Engine.h"
#include <memory>
#include "SnakeSprite.h"
#include "FoodSprite.h"
#include <iostream>

using namespace snake;
using namespace std;

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cerr << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }
    
    SpritePtr snake = std::make_shared<SnakeSprite>(&eng);
    SpritePtr food = std::make_shared<FoodSprite>(100, 100);
    
    // Give food a reference to the snake
    std::dynamic_pointer_cast<FoodSprite>(food)->setSnake(snake);
    
    eng.add(snake);
    eng.add(food);
    eng.run();

    SDL_Quit();
    return 0;
}