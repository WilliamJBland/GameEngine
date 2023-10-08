#pragma once

#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"
#include <iostream>
#include <vector>
#include <game_object.h>


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
        void addGameObject(GameObject* gameObject);

        // static void addTile(int id, int x, int y);
        static SDL_Renderer *renderer;
        static SDL_Event event;
        // static std::vector<ColliderComponent*> colliders;
    
    private:
        bool isRunning;
        int cnt;
        SDL_Window *window;
        std::vector<GameObject*> liveGameObjects;
};
