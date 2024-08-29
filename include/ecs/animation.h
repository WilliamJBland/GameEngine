#pragma once

#include <vector_2d.h>


struct Animation
{
    Vector2D index;
    int frames;
    int speed;

    Animation() {}
    Animation(Vector2D i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
    }
};