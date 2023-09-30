#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"


class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* textureFileName, SDL_Renderer* renderer);

};
