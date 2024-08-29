#pragma once

#include "SDL.h"


class ColliderComponent;

class Collision
{
    public:
        // don't want to have an instance of the class to check this collision therefore static
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
        static bool AABB(const ColliderComponent& colA, ColliderComponent& colB);
};