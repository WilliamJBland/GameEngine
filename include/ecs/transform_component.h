#pragma once

#include <vector_2d.h>


class TransformComponent : public Component
{
public:

    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 2;

    int speed = 3;

    TransformComponent()
    {
        position.x = 320;
        position.y = 250;
    }
    
    TransformComponent(int sc)
    {
        position.x = 320;
        position.y = 250;
        scale = sc;
    }

    TransformComponent(float x, float y, int sc)
    {
        position.x = x;
        position.y = y;
        scale = sc;
    }
    
    TransformComponent(float x, float y, int h, int w, int sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }


    void init() override
    {
        velocity.zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};