#pragma once

#include <map>
#include <string>
#include <texture_manager.h>
#include <vector_2d.h>
#include <ecs/ecs.h>



class AssetManager
{
    public:
        AssetManager(EntityManager* man);
        ~AssetManager();

        // Game objects
        void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, int scale);

        // texture management
        void addTexture(std::string id, const char* path);
        SDL_Texture* getTexture(std::string id);

        std::map<std::string, SDL_Texture*> textures;

    private:

        EntityManager* manager;
        
};