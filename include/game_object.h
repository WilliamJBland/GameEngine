#pragma once
#include "SDL2/SDL.h"

class GameObject {

    public:
        GameObject(const char* textureSheet, SDL_Renderer* renderer);
        ~GameObject();

        void update();
        void render();

        int xPos;
        int yPos;
        

    private:
      

        SDL_Texture* objectTexture;
        SDL_Rect sourceRect, destinationRect;
        SDL_Renderer* renderer;


};