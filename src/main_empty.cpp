#include "Engine.h"
#include <memory>
#include "SnakeSprite.h"
#include "FoodSprite.h"
#include <iostream>
#include "MainMenu.h"

using namespace snake;
using namespace std;

int main(int argc, char* argv[]) {

    TTF_Init();    
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        cerr << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }
    
    
    // Ladda ljudeffekter
    for(int i = 1; i <= 8; i++){
        std::string name = "eat" + std::to_string(i);
        std::string file = cnts::gResPath + "sounds/snakebite" + 
                          std::to_string(i) + ".wav";
        eng.loadSound(name, file);
    }

    MainMenu menu(&eng);
    menu.run();  // Kör menyn

    // Ladda bakgrundsmusik
    eng.loadBackgroundMusic(cnts::gResPath + "sounds/Snakemusik.wav");
    eng.setMusicVolume(0.3);  // 30% volym
    eng.playBackgroundMusic(true);  // Loop = true
    
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