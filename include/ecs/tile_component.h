#pragma once

#include <ecs/ecs.h>
#include "SDL.h"




class TileComponent : public Component
{
    public:

        SDL_Texture* texture;
        SDL_Rect srcRect, destRect;
        Vector2D position;


        TileComponent() = default;

        ~TileComponent()
        {
            SDL_DestroyTexture(texture);
        }

        TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string tID)
        {
            texture = Game::assets->getTexture(tID);
            position.x = xpos;
            position.y = ypos;

            srcRect.x = srcX;
            srcRect.y = srcY;
            srcRect.w = srcRect.h = tsize;


            destRect.x = xpos;
            destRect.y = ypos;
            destRect.w = destRect.h = tsize * tscale;
        }

        void update() override
        {
            destRect.x = position.x - Game::camera.x;
            destRect.y = position.y - Game::camera.y;

        }

        void draw() override
        {
            TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
        }

};