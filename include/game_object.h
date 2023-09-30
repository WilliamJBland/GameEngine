#pragma once
#include "SDL2/SDL.h"

class GameObject {

    public:
        GameObject(const char* textureSheet, int x=0, int y=0);
        ~GameObject();

        void update();
        void render();
        void setSprite(const char* textureSheet);

        int xPos;
        int yPos;
        

    private:
        SDL_Texture* objectTexture;
        SDL_Rect sourceRect, destinationRect;
};