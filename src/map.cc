#include "map.hh"
#include <cstdlib>
#include <vector>


char **&Map::getMap() {
    return map_;
}

int Map::getHeight() {
    return height_;
}

int Map::getWidth() {
    return width_;
}


void Map::displayMap()
{
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            std::cout << "|" << getMap()[i][j] << "|";
        }
        std::cout << std::endl;
    }
}


