#include <game.h>
#include <game_object.h>
#include <texture_manager.h>


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

GameObject* playerObject;

Game::Game(){}
Game::~Game(){}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
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

     playerObject = new GameObject("/Users/williambland/code/GameEngine/assets/WizardIdle.bmp", renderer);
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
                    playerObject->yPos -= speed;
                    break;
                case SDLK_DOWN:
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
    playerObject->update();
    std::cout << playerObject->xPos << ", " << playerObject->yPos << std::endl;
    return;
}

void Game::render() {
    SDL_RenderClear(renderer);
    playerObject->render();
    SDL_RenderPresent(renderer);

}
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}