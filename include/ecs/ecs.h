#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;

// Define a new type alias ComponentID which is the size_t type
using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    // Static means the code will reuse the variable and so keep state on repeated calls. This result in incrementing the ID
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}


class Component
{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

 
 // Max number of components an entity can hold
constexpr std::size_t maxComponents = 32;


constexpr std::size_t maxGroups = 32;

// Allows comparing entities to see if there is a match on entities
using ComponentBitSet = std::bitset<maxComponents>;

using GroupBitSet = std::bitset<maxGroups>;

// Array of component pointers the length of our max number of components
using ComponentArray = std::array<Component*, maxComponents>;

class EntityManager;

class Entity
{
private:
    EntityManager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(EntityManager& mManager) : manager(mManager) {}
    void update()
    {
       for (auto& c : components) c->update();
    }

    void draw() {
        for (auto& c : components) c->draw();
    }
    bool isActive() const { return active; }
    void destroy() { active = false; }

    bool hasGroup(Group mGroup)
    {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }

    // Check if entity has a component by passing the type of that component
    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }
    

    // add a component of type T. Create a T pointer c which points to a new T with the mArgs forwarded to it.
    // set the entity of c (the newly created component of some type T) to the current entity i.e. creating a component for the current entity
    // Create a unique pointer to the component c and push this pointer onto the components vector of the entity.
    // get the id of the component and then insert the new component c into the component array at that location.
    // Set the bitset to true for checking.
    // initialise the new component and return a pointer to it.
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c = new T(std::forward<TArgs>(mArgs)...);
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));
 
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    // get the ID of the type of component, access it from the component array and return a pointer to that component.
    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
          
};


class EntityManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    void update();
    void draw();
    void refresh();
    void AddToGroup(Entity* mEntity, Group mGroup);

    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }
    Entity& addEntity();
};