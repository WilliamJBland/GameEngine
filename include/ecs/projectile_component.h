#pragma once


#include <ecs/ecs.h>
#include <ecs/components.h>
#include <vector_2d.h>



class ProjectileComponent : public Component
{
    public:
    // This makes you pass a scalar speed and a velocity but does not enforce sensible values. The distance is then calculated from 
    // the speed which could be 0 whilst the velocity > 0
        ProjectileComponent(int rng, Vector2D vel) : range(rng), speed(vel.absolute()), velocity(vel) {}
        ~ProjectileComponent() {}

        void init() override 
        {
            transform = &entity->getComponent<TransformComponent>();
            transform->velocity = velocity;
        }
        void update() override 
        {
            distance += speed;
            if (distance > range) {
                entity->destroy();
            }
            else if (transform->position.x > Game::camera.x + Game::camera.w ||
                     transform->position.x < Game::camera.x ||
                     transform->position.y > Game::camera.y + Game::camera.h ||
                     transform->position.y < Game::camera.y)
            {
                entity->destroy();
            }
        }
        

    private:
        TransformComponent* transform;

        int range = 0;
        int speed = 0;
        int distance = 0;
        Vector2D velocity;
};