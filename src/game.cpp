#include "../include/game.h"


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialised" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer Created" << std::endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }
}