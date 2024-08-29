#include <map.h>
#include <game.h>
#include <fstream>
#include <ecs/ecs.h>
#include <ecs/components.h>



extern EntityManager manager;


Map::Map(std::string tID, int mScale, int tSize) : texID(tID), mapScale(mScale), tileSize(tSize)
{
    scaleSize = mScale * tSize;
}

Map::~Map()
{
}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for (int y = 0; y < sizeY; y++) 
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            addTile(srcX, srcY, x * scaleSize, y * scaleSize);
            mapFile.ignore();
        }
    }

    mapFile.ignore();
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);

            if (c == '1')
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("terrain", x * scaleSize, y * scaleSize, scaleSize);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
    tile.addGroup(Game::groupMap);
}
