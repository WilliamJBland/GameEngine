#include "game_object.h"
#include "texture_manager.h"


GameObject::GameObject(const char* textureSheetFile, SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    objectTexture = TextureManager::LoadTexture(textureSheetFile, ren);
    xPos = x;
    yPos = y;

}

void GameObject::update() {

    sourceRect.h = 32;
    sourceRect.w = 32;
    sourceRect.x = 0;
    sourceRect.y = 0;

    destinationRect.x = xPos;
    destinationRect.y = yPos;
    destinationRect.w = sourceRect.w * 2;
    destinationRect.h = sourceRect.h * 2;
}

void GameObject::render() {
    SDL_RenderCopy(renderer, objectTexture, NULL, &destinationRect);
}