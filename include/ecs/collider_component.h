#pragma once

#include <string>
#include "SDL.h"
#include <ecs/ecs.h>
#include <ecs/transform_component.h>
#include <texture_manager.h>
#include <game.h>



class ColliderComponent : public Component
{  
public:
    SDL_Rect collider;
    std::string tag;

    //for displaying collision texture
    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;


    TransformComponent* transform;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    ColliderComponent(std::string t, int xPos, int yPos, int size)
    {
        tag = t;
        collider.x = xPos;
        collider.y = yPos;
        collider.h = collider.w = size;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        tex = TextureManager::LoadTexture("../assets/terrain_collision.xcf");
        srcRect = {0, 0, 32, 32};
        destRect = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override
    {
        if (tag != "terrain") 
        {
            collider.x = transform->position.x;
            collider.y = transform->position.y;
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }

        destRect.x = collider.x - Game::camera.x;
        destRect.y = collider.y - Game::camera.y;
        
    }


    void draw() override 
    {
        TextureManager::draw(tex, srcRect, destRect, SDL_FLIP_NONE);
    }

};