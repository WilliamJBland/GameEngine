#include <game.h>


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Texture* playerTexture;
SDL_Rect sourceRect, destinationRect;

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
    SDL_Surface* tempSurface = IMG_Load("/Users/williambland/code/GameEngine/assets/WizardIdle.bmp");
    playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
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
                    destinationRect.x -= speed;
                    break;
                case SDLK_RIGHT:
                    destinationRect.x += speed;
                    break;
                case SDLK_UP:
                    destinationRect.y -= speed;
                    break;
                case SDLK_DOWN:
                    destinationRect.y += speed;
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}

void Game::update() {
    int scale = 2;
    destinationRect.h = 32 * scale;
    destinationRect.w = 32 * scale;
    std::cout << destinationRect.x << std::endl;
    return;
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, NULL, &destinationRect);
    SDL_RenderPresent(renderer);

}
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}