#include <ecs/ecs.h>



void EntityManager::update()
{
    for (auto& e : entities) e->update();
}
    

void EntityManager::draw()
{
    for (auto& e : entities) e->draw();
}

void EntityManager::refresh()
{
    for (auto i(0u); i < maxGroups; i++)
    {
        auto& v(groupedEntities[i]);
        v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
        {
            return !mEntity->isActive() || !mEntity->hasGroup(i);
        }),
        std::end(v));
    }
    entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
    {
        return !mEntity->isActive();
    }),
    std::end(entities));
}

void EntityManager::AddToGroup(Entity* mEntity, Group mGroup)
{
    groupedEntities[mGroup].emplace_back(mEntity);
}



Entity& EntityManager::addEntity()
{
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));
    return *e;
}

void Entity::addGroup(Group mGroup)
{
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}