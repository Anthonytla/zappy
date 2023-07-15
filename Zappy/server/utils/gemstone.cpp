#include "../server.hh"

void Server::gemstonesInit()
{
    _gemStonesArray.push_back(new Linemate);
    _gemStonesArray.push_back(new Deraumere);
    _gemStonesArray.push_back(new Sibur);
    _gemStonesArray.push_back(new Mendiane);
}

void Server::generateStone()
{
    char mapValues[8] = {'1', '2', '3', '4', 'L', 'D', 'S', 'M'};

    int stoneY = generateRandNum(0, this->_map_height - 1);
    int stoneX = generateRandNum(0, this->_map_width - 1);

    if (this->map[stoneY][stoneX] == ' ')
    {
        this->map[stoneY][stoneX] = mapValues[generateRandNum(4, 7)];
    }
}

void Server::pickUpStone(short int id,int newX, int newY) {
    for (size_t i = 0; i < _gemStonesArray.size(); i++) {
        if (this->map[newY][newX] == _gemStonesArray[i]->getName()) {
            _gemStonesArray[i]->applyEffect(_playersArray, id);
            this->map[newY][newX] = ' ';
            return;
        }
    }
}