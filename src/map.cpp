#include <map.h>
#include <texture_manager.h>


int lvl1[20][25] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,1,1,1,1,1,1,2,0,0,0,0,0,0},
    {0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,2,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
    {0,0,0,2,1,1,1,1,1,1,1,1,1,2,2,0,0,0,0,0},
    {0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0},
    {0,0,0,0,2,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0},
    {0,0,0,0,0,0,2,2,2,1,1,1,2,2,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


Map::Map() {
    water = TextureManager::LoadTexture("/Users/williambland/code/GameEngine/assets/WaterBase.png");
    dirt = TextureManager::LoadTexture("/Users/williambland/code/GameEngine/assets/DirtBase.png");
    grass = TextureManager::LoadTexture("/Users/williambland/code/GameEngine/assets/GrassBase.png");

    loadMap(lvl1);

    source.x = source.y = 0;
    source.w = destination.w = 32;
    source.h = destination.h = 32;

    destination.x = destination.y = 0;
}

void Map::loadMap(int arr[20][25]) {
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 25; col++) {
            map[row][col] = arr[row][col];
        }
    }
}

void Map::drawMap() {
    int type = 0;
    std::cout << "Draw Map called" << std::endl;
    
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 25; col++) {
            
            type = map[row][col];
            destination.x = col * 32;
            destination.y = row * 32;
            switch (type) {
                case 0:
                    TextureManager::draw(water, source, destination);
                    break;
                case 1:
                    TextureManager::draw(grass, source, destination);
                    break;
                case 2:
                    TextureManager::draw(dirt, source, destination);
                    break;
                default:
                    break;
            }
        }
    }
}