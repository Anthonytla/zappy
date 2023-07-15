#include "../server.hh"

void Server::playerInit(short int id, sf::TcpSocket *tcpSocket, int x, int y)
{
    std::string orientation;
    if (id < 3)
    {
        orientation = "North";
    }
    else if (id >= 3)
    {
        orientation = "South";
    }
   // std::cout << std::to_string(id)[0] << std::endl;
    this->map[y][x] = std::to_string(id)[0];
    Player *newPlayer = new Player(x, y, id, 0, orientation, tcpSocket);
    _playersArray.at(id - 1) = newPlayer;
}

void Server::displayPlayersInfo()
{
    for (size_t i = 0; i < _playersArray.size(); i++)
    {
        if (_playersArray.at(i))
        {
            std::cout << "Player " << _playersArray[i]->getId() << " : life " << _playersArray[i]->getLife() << " victory " << _playersArray[i]->getVictory() << std::endl;
        }
    }
}

void Server::removeDeadPlayers()
{
    for (size_t i = 0; i < _playersArray.size(); i++){
        if (_playersArray.at(i) && _playersArray[i]->getLife() <= 0) {
            std::cout << "Player " << _playersArray[i]->getId() << " is dead..." << std::endl;
            disconnectClient(_playersArray[i]->getTcpSocket(), _playersArray[i]->getId() - 1);
        }
    }
    std::cout << "Checking dead players !" << std::endl;
}

int Server::getWinningPlayer()
{
    for (size_t i = 0; i < _playersArray.size(); i++)
    {
        if (_playersArray.at(i))
        {
            if (nbConnected == 1 || _playersArray[i]->getVictory() >= 10) 
            {
                return i;
            }
        }
    }
    return -1;
}