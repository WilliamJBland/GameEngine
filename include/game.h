#ifndef game_hpp
#define game_hpp
#include "SDL2/SDL.h"
#include <iostream>


class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        
        bool running() {return isRunning; };

    private:
        bool isRunning;
        int cnt;
        SDL_Window *window;
        SDL_Renderer *renderer;

};

#endif /* game_hpp */