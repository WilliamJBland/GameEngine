#include <game.h>
#include <texture_manager.h>
#include <map.h>



SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

GameObject* playerObject;
GameObject* player2Object;

Map* map;

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

     playerObject = new GameObject("/Users/williambland/code/GameEngine/assets/WizardIdle.bmp");
     player2Object = new GameObject("/Users/williambland/code/GameEngine/assets/ElfIdle.xcf", 68, 68);
     map = new Map();
     this->addGameObject(playerObject);
     this->addGameObject(player2Object);
}

void Game::handleEvents(){
    SDL_PollEvent(&event);
    int speed = 8;
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    playerObject->xPos -= speed;
                    break;
                case SDLK_RIGHT:
                    playerObject->xPos += speed;
                    break;
                case SDLK_UP:
                    playerObject->setSprite("/Users/williambland/code/GameEngine/assets/WizardIdleBack.bmp");
                    playerObject->yPos -= speed;
                    break;
                case SDLK_DOWN:
                    playerObject->setSprite("/Users/williambland/code/GameEngine/assets/WizardIdle.bmp");
                    playerObject->yPos += speed;
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void Game::update() {
    for (auto gameObject : liveGameObjects) {
        gameObject->update();
    }
    return;
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();
    for (auto gameObject : liveGameObjects) {
        gameObject->render();
    }
    SDL_RenderPresent(renderer);

}
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

void Game::addGameObject(GameObject* gameObject) {
    liveGameObjects.push_back(gameObject);
}