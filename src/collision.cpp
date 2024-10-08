#include <collision.h>
#include <ecs/collider_component.h>


bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y
    ) {
        return true;
    }
    return false;
}


bool Collision::AABB(const ColliderComponent& colA, ColliderComponent& colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        return true;
    }
    else {
        return false;
    }
}