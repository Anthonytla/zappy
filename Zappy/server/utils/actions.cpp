#include "../server.hh"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void Server::executeAction(int idx, std::string command) {
    std::string meReturn;
    std::string inspectReturn;
    std::vector<json> infosClient;
    bool status = move(command, idx);
    json response; 
    command.pop_back();
    sf::Packet sendPacket;
    if (command != "me" && command != "inspect" && command != "map")
    {
       
        response[command] = status ? "OK" : "KO";
        sendPacket << response.dump();
        
    }
    else if (command == "me")
    {
        meReturn = "{\"me\": \n {\"id\":" + std::to_string(_playersArray[idx]->getId()) + ", \"life\":" + std::to_string(_playersArray[idx]->getLife()) + ", \"energy\":" + std::to_string(_playersArray[idx]->getEnergy()) + ", \"victory\":" + std::to_string(_playersArray[idx]->getVictory()) + ", \"orientation\":" + "\"" + _playersArray[idx]->getOrientation() + "\"}  \n }";
        sendPacket << meReturn;
        
    }
    else if (command == "inspect")
    {
        std::vector<json> infosClient;
        inspectReturn = "{\"inspect\": [ \n";
        for (size_t i = 0; i < _playersArray.size(); i++)
        {
            if (_playersArray.at(i)){
                inspectReturn += "{\"id\": " + std::to_string(_playersArray[i]->getId()) + ", \"life\": " + std::to_string(_playersArray[i]->getLife()) + ", \"victory\": " + std::to_string(_playersArray[i]->getVictory()) + "}";
                if (i != _playersArray.size() - 1)
                    inspectReturn += ",\n";
                else 
                    inspectReturn += "\n";
            }
        }
        inspectReturn += "]} \n";

    }
    sendPacket << inspectReturn;
    clients[idx]->send(sendPacket);
    
    if (status)
        std::cout << "player "<<idx + 1<<" executed "<<command << " with status: "<< status<< std::endl;
}

int getOrientationIndex(std::string orientation)
{
    std::string orientations[4] = {"North", "East", "South", "West"};
    for (int i = 0; i < 4; i++)
    {
        if (orientation == orientations[i])
        {
            return i;
        }
    }
    return 0;
}

void Server::updatePlayerOrientation(short int id, std::string orientationDirection)
{
    std::string currentOrientation = _playersArray[id]->getOrientation();
    std::string orientations[4] = {"North", "East", "South", "West"};
    int orientationIndex = getOrientationIndex(currentOrientation);
    if (orientationDirection == "right")
    {
        _playersArray[id]->setOrientation(orientations[(orientationIndex + 1) % 4]);
    }
    else if (orientationDirection == "left")
    {
        _playersArray[id]->setOrientation(orientations[(orientationIndex - 1 + 4) % 4]);
    }
}

bool Server::checkPlayerAround(int id, int newX, int newY) {
    for (size_t i = 0; i < _playersArray.size(); i++) {
        if (_playersArray.at(i) && static_cast<int>(i) != id && _playersArray[i]->getY() == newY && _playersArray[i]->getX() == newX) {
            short int currentLife = _playersArray[i]->getLife();
            std::cout << "Player " << id + 1 << " attacks player " << i + 1 << std::endl;
            _playersArray[i]->setLife(currentLife - 1);
            return true;
        }
    }
    return false;
}

bool Server::updatePlayerPosition(short int id, int step)
{
    std::string currentOrientation = _playersArray[id]->getOrientation();
    int currentX = _playersArray[id]->getX();
    int currentY = _playersArray[id]->getY();
    if (currentOrientation == "North") {
        if (currentY - step < 0 || abs(currentY - step) > _map_height - 1 || checkPlayerAround(id, currentX, currentY - step)) {return false;}
        pickUpStone(id, currentX, currentY - step);
        _playersArray[id]->setY(currentY - step);
    } else if (currentOrientation == "East") {
        if (currentX  + step < 0 || abs(currentX + step) > _map_width - 1 || checkPlayerAround(id, currentX + step, currentY)) {return false;}
        pickUpStone(id, currentX + step, currentY);
        _playersArray[id]->setX(currentX + step);
    } else if (currentOrientation == "South") {
        if (currentY  + step < 0 || abs(currentY  + step) > _map_height - 1 || checkPlayerAround(id, currentX, currentY + step)) {return false;}
        pickUpStone(id, currentX, currentY + step);
        _playersArray[id]->setY(currentY + step);
    } else if (currentOrientation == "West") {
        if (currentX - step < 0 || abs(currentX - step) > _map_width - 1 || checkPlayerAround(id, currentX - step, currentY)) {return false;}
        pickUpStone(id, currentX - step, currentY);
        _playersArray[id]->setX(currentX - step);
    }
    map[currentY][currentX] = ' ';
    return true;
}

bool Server::updatePlayerStats(short int id, short int energyCost, std::string orientationDirection, int step)
{
    short int currentEnergy = _playersArray[id]->getEnergy();
    if (currentEnergy >= energyCost)
    {
        _playersArray[id]->setEnergy(currentEnergy - energyCost);
        updatePlayerOrientation(id, orientationDirection);
        return updatePlayerPosition(id, step);
    }
    return false;
}

bool Server::move(std::string command, int id)
{
    if (command == "right\n")
    {
        return updatePlayerStats(id, 1, "right");
    }
    else if (command == "left\n")
    {
        return updatePlayerStats(id, 1, "left");
    }
    else if (command == "fwd\n")
    {
        return updatePlayerStats(id, 1, "none", 1);
    }
    else if (command == "leftfwd\n")
    {
        return updatePlayerStats(id, 1, "left", 1);
    }
    else if (command == "rightfwd\n")
    {
        return updatePlayerStats(id, 1, "right", 1);
    }
    else if (command == "back\n")
    {
        return updatePlayerStats(id, 1, "none", -1);
    }
    else if (command == "jump\n")
    {
        return updatePlayerStats(id, 1, "none", 3);
    }
    return false;
}