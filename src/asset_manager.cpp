#include <asset_manager.h>
#include <ecs/components.h>


AssetManager::AssetManager(EntityManager* man) : manager(man)
{}

AssetManager::~AssetManager() 
{}

void AssetManager::addTexture(std::string id, const char* path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
    return textures[id];
}

void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, int scale)
{
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale);
    projectile.addComponent<SpriteComponent>(id, false);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupProjectiles);

}