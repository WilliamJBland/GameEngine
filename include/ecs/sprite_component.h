#pragma once

#include <texture_manager.h>
#include <ecs/components.h>
#include <ecs/animation.h>
#include <map>
#include <SDL.h>
#include <vector_2d.h>
#include <game.h>
#include <asset_manager.h>


class SpriteComponent : public Component
{
    private:
        TransformComponent *transform_component;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int frames = 0;
        int speed = 100;

    public:

        Vector2D animIndex;

        std::map<const char*, Animation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent() = default;

        SpriteComponent(std::string tID) {
            setTexture(tID);
        }

        SpriteComponent(std::string tID, bool isAnimated) {
            
            animated = isAnimated;

            Animation idle = Animation(Vector2D(0, 0), 4, 200);
            Animation walk = Animation(Vector2D(0, 1), 4, 400);
            Animation power = Animation(Vector2D(0, 2), 4, 400);

            animations.emplace("Idle", idle);
            animations.emplace("Walk", walk);
            animations.emplace("Power", power);

            
            play("Idle");
            setTexture(tID);

        }

        ~SpriteComponent()
        {}

        void setTexture(std::string tID)
        {
            texture = Game::assets->getTexture(tID);
        }

        void init() override
        {
            transform_component = &entity->getComponent<TransformComponent>();
            
            srcRect.x = srcRect.y = 0;
            srcRect.w = transform_component->width; 
            srcRect.h = transform_component->height;
        }

        void update() override
        {
            if (animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }

            srcRect.y = animIndex.y * transform_component->height;
            
            destRect.x = static_cast<int>(transform_component->position.x) - Game::camera.x;
            destRect.y = static_cast<int>(transform_component->position.y) - Game::camera.y;
            destRect.w = transform_component->width * transform_component->scale;
            destRect.h = transform_component->height * transform_component->scale;
        }

        void draw() override
        {
            TextureManager::draw(texture, srcRect, destRect, spriteFlip);
        }

        void play(const char* animName)
        {
            frames = animations[animName].frames;
            animIndex = animations[animName].index;
            speed = animations[animName].speed;
        }

};