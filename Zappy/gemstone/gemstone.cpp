#include "gemstone.hh"

char GemStone::getName()
{
    return this->name;
}

char Linemate::getName()
{
    return this->name;
}

void Linemate::applyEffect(std::vector<Player*> playersArray, short int id)
{
    short int currentLife = playersArray[id]->getLife();
    playersArray[id]->setLife(currentLife + 1);
    std::cout << "Player " << playersArray[id]->getId() << " finds a LINEMATE : life "<<playersArray[id]->getLife() << std::endl;
}

char Deraumere::getName()
{
    return this->name;
}

void Deraumere::applyEffect(std::vector<Player*> playersArray, short int id)
{
    short int currentLife = playersArray[id]->getLife();
    if (currentLife > 0) {
        playersArray[id]->setLife(currentLife - 1);
    }
    std::cout << "Player " << playersArray[id]->getId() << " finds a DERAUMERE : life "<<playersArray[id]->getLife() << std::endl;
}

char Sibur::getName()
{
    return this->name;
}

void Sibur::applyEffect(std::vector<Player*> playersArray, short int id)
{
    for (size_t i = 0; i < playersArray.size(); i++) {
        if (playersArray.at(i) && playersArray[i]->getId() - 1 != id) {
            if (playersArray[i]->getLife() > 0)
                playersArray[i]->setLife(playersArray[i]->getLife() - 1);
        }
    }
    std::cout << "Player " << playersArray[id]->getId() << " finds a SIBUR : life "<<playersArray[id]->getLife() << std::endl;
}

char Mendiane::getName()
{
    return this->name;
}

void Mendiane::applyEffect(std::vector<Player*> playersArray, short int id)
{
    short int currentVictory = playersArray[id]->getVictory();
    playersArray[id]->setVictory(currentVictory + 1);
    std::cout << "Player " << playersArray[id]->getId() << " finds a MENDIANE : victory "<<playersArray[id]->getVictory() << std::endl;
}