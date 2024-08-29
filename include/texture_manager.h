#pragma once

#include "SDL.h"
#include "SDL_Image.h"


class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* textureFileName);
        static void draw(SDL_Texture* tex, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip);
};
