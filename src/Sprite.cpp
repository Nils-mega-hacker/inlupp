#include "Sprite.h"

using namespace std;

namespace snake{

    Sprite::Sprite(float x, float y, float w, float h) : image(nullptr) {
        rect = {x, y, w, h};
    }

    Sprite::Sprite(string name,float x,float y){
        image = IMG_LoadTexture(eng.getRen(), (cnts::gResPath + "/images/" + name).c_str());
        if (!image){
            cerr << "No such file: " << name << endl;
            exit(EXIT_FAILURE);
        }
        rect = {x,y,static_cast<float>(image->w),static_cast<float>(image->h)};
    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(image);
    }


    void Sprite::draw() const{
        if (image)
            SDL_RenderTexture(eng.getRen(), image, NULL, &rect);
    }

    bool Sprite::collidedWith(SpritePtr other) const{
        return SDL_HasRectIntersectionFloat(&rect, &other->rect);
    }

}