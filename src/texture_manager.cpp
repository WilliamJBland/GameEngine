#include <texture_manager.h>
#include <game.h>


SDL_Texture* TextureManager::LoadTexture(const char* textureFileName) {
    SDL_Surface* tempSurface = IMG_Load(textureFileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect source, SDL_Rect destination) {
    SDL_RenderCopy(Game::renderer, tex, &source, &destination);
}