#pragma once

#include <game.h>
#include <ecs/ecs.h>


class KeyboardController : public Component
{
    public:
        TransformComponent *transform;
        SpriteComponent * sprite;

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }

        void update() override
        {
            if (Game::event.type == SDL_KEYDOWN) 
            {
                switch (Game::event.key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.y = -1;
                        sprite->play("Walk");
                        break;
                    case SDLK_s:
                        transform->velocity.y = 1;
                        sprite->play("Walk");
                        break;
                    case SDLK_a:
                        transform->velocity.x = -1;
                        sprite->play("Walk");
                        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_d:
                        transform->velocity.x = 1;
                        sprite->play("Walk");
                        break;
                    case SDLK_f:
                        sprite->play("Power");
                            Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(1, 0), 10, 0, "projectile", 2);
                            Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(-1, 0), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(0, 1), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(0, -1), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(0, -1), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(-1, -1), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(1, 1), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(1, -1), 10, 0, "projectile", 2);
                            // Game::assets->createProjectile(Vector2D(transform->position.x, transform->position.y), Vector2D(-1, 1), 10, 0, "projectile", 2);
                        break;
                    default:
                        break;
                }
            }

            if (Game::event.type == SDL_KEYUP)
            {
                switch (Game::event.key.keysym.sym)
                {
                    case SDLK_w:
                        transform->velocity.y = 0;
                        sprite->play("Idle");
                        break;
                    case SDLK_s:
                        transform->velocity.y = 0;
                        sprite->play("Idle");
                        break;
                    case SDLK_a:
                        transform->velocity.x = 0;
                        sprite->play("Idle");
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        break;
                    case SDLK_d:
                        transform->velocity.x = 0;
                        sprite->play("Idle");
                        break;
                    case SDLK_f:
                        sprite->play("Idle");
                        break;
                    case SDLK_ESCAPE:
                        Game::isRunning = false;
                        break;
                }
            }
        }
};