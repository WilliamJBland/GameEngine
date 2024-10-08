#pragma once

#include "SDL.h"
#include "SDL_Image.h"
#include <iostream>
#include <vector>
#include <game_object.h>



class AssetManager;
class ColliderComponent;



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

        static SDL_Renderer *renderer;
        static SDL_Event event;

        static bool isRunning;
        static SDL_Rect camera;
        static AssetManager* assets;

        enum groupLabels : std::size_t
            {
                groupMap,
                groupPlayers,
                groupColliders,
                groupProjectiles
            };

    private:
        int cnt;
        SDL_Window *window;
        std::vector<GameObject*> liveGameObjects;
};
