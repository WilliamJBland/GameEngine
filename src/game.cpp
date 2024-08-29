#include <game.h>
#include <texture_manager.h>
#include <map.h>
#include <ecs/components.h>
#include <ecs/keyboard_controller.h>
#include <collision.h>
#include <asset_manager.h>



Map* map;
EntityManager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 800, 640};

AssetManager* Game::assets = new AssetManager(&manager);
bool Game::isRunning = false;


// This is syntax for creating a variable player and assigning it to the entity returned by addEntitye
auto& player(manager.addEntity());


Game::Game(){}
Game::~Game(){}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    std::vector<GameObject*> liveGameObjects = {};
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialised" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (window) {
            SDL_SetRenderDrawColor(renderer, 255, 1, 255, 255);
            std::cout << "Window Created" << std::endl;
        }
        
        if (renderer) {
            std::cout << "Renderer Created" << std::endl;
        }
        	 
        isRunning = true;
    } else {
        isRunning = false;
    }


    assets->addTexture("terrain", "../assets/terrain.xcf");
    assets->addTexture("player", "../assets/WizardSpriteSheetNew.xcf");
    assets->addTexture("projectile", "../assets/WizardFire.xcf");


    map = new Map("terrain", 2, 32);
    map->loadMap("../assets/lvl1_16x16.txt", 22, 16);

    player.addComponent<TransformComponent>(500, 600, 2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);


}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents(){
    SDL_PollEvent(&event);
    int speed = 8;
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;


    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }
    for (auto& p : projectiles)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
        {
            std::cout << "Hit player" << std::endl;
            // p->destroy();
        }
    }
    camera.x = player.getComponent<TransformComponent>().position.x - 300;
    camera.y = player.getComponent<TransformComponent>().position.y - 250;

    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > camera.w)
    {
        camera.x = camera.w;
    }
    if (camera.y > camera.h)
    {
        camera.y = camera.h;
    }
}


void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& t : tiles)
    {
        t->draw();
    }
    for (auto& c : colliders)
    {
        c->draw();
    }
    for (auto& p : players)
    {
        p->draw();
    }
    for (auto& p : projectiles)
    {
        p->draw();
    }


    SDL_RenderPresent(renderer);

}
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
