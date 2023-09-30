#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"
#include <iostream>


class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        bool running(){return isRunning; };
        void render();
        void clean();

        // static void addTile(int id, int x, int y);
        static SDL_Renderer *renderer;
        static SDL_Event event;
        // static std::vector<ColliderComponent*> colliders;
    
    private:
        bool isRunning;
        int cnt;
        SDL_Window *window;
};
