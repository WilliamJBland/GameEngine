#include <texture_manager.h>


SDL_Texture* TextureManager::LoadTexture(const char* textureFileName, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(textureFileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}