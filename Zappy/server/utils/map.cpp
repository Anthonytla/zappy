#include "../server.hh"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void Server::mapInit()
{
    this->map = new char *[_map_height];
    for (int count = 0; count < _map_height; count++)
    {
        map[count] = new char[_map_width];
    }
    for (int i = 0; i < _map_height; i++)
    {
        for (int j = 0; j < _map_width; j++)
        {
            char a = ' ';
            map[i][j] = a;
        }
    }
}

void Server::sendMap() {
    for (size_t i = 0; i < _playersArray.size(); i++) {
        if (_playersArray.at(i))
        {
            sf::Packet sendPacket;
            int x = _playersArray[i]->getX();
            int y = _playersArray[i]->getY();
            std::string orientation = _playersArray[i]->getOrientation();
            std::vector<std::string> mapping;
            mapping = getMap(y, x, orientation, map);
            json response;
            response["map"] = mapping;
            sendPacket << response.dump();
            _playersArray[i]->getTcpSocket()->send(sendPacket);
        }
    } 
}

std::vector<std::string> Server::getMap(int x, int y, std::string orientation, char **map)
{
    std::vector<std::string> returning;
    if (orientation == "North")
        returning = getMapNorth(x, y, map);
    if (orientation == "South")
        returning = getMapSouth(x, y, map);
    if (orientation == "East")
        returning = getMapEast(x, y, map);
    if (orientation == "West")
        returning = getMapWest(x, y, map);
    return returning;
}

std::vector<std::string> Server::getMapNorth(int x, int y, char **map)
{
    //std::cout << x << y << std::endl;
    std::vector<std::string> returning;
    if (x - 1 >= 0 && y - 1 >= 0) {
    //    std::cout << map[x-1][y-1] << std::endl;
        std::string s(1, map[x-1][y-1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x - 1 >= 0) {
    //    std::cout << map[x-1][y] << std::endl;
        std::string s(1, map[x-1][y]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x - 1 >= 0 && y + 1 < _map_width) {
     //   std::cout << map[x-1][y+1] << std::endl;
        std::string s(1, map[x-1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x - 2 >= 0) {
      //  std::cout << map[x-2][y] << std::endl;
        std::string s(1, map[x-2][y]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    return returning;
}

std::vector<std::string> Server::getMapSouth(int x, int y, char **map)
{
    std::vector<std::string> returning;
    if (x + 1 < _map_height && y + 1 < _map_width) {
        std::string s(1, map[x+1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 1 < _map_height){
        std::string s(1, map[x+1][y]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 1 < _map_height && y - 1 >= 0){
        std::string s(1, map[x+1][y-1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 2 < _map_height){
        std::string s(1, map[x+2][y]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    return returning;
}

std::vector<std::string> Server::getMapEast(int x, int y, char **map)
{
    std::vector<std::string> returning;
    if (x - 1 >= 0 &&  y + 1 < _map_width){
        std::string s(1, map[x-1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (y + 1 < _map_width){
        std::string s(1, map[x][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 1 < _map_height && y + 1 < _map_width){
        std::string s(1, map[x+1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (y + 2 < _map_width){
        std::string s(1, map[x][y+2]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    return returning;
}

std::vector<std::string> Server::getMapWest(int x, int y, char **map)
{
    std::vector<std::string> returning;
    if (x + 1 < _map_height && y - 1 >= 0){
        std::string s(1, map[x+1][y-1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (y - 1 >= 0){
        std::string s(1, map[x][y - 1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x - 1 >= 0 && y - 1 >= 0){
        std::string s(1, map[x - 1][y - 1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (y - 2 >= 0){
        std::string s(1, map[x][y - 2]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    return returning;
}

void Server::displayMap()
{
    for (int i = 0; i < _map_height; i++)
    {
        for (int j = 0; j < _map_width; j++)
        {
            std::cout << "|" << map[i][j] << "|";
        }
        std::cout << std::endl;
    }
}

void Server::mapUpdate()
{
    for (size_t i = 0; i < _playersArray.size(); i++)
    {
        if (_playersArray.at(i)) 
        {
            int x = _playersArray[i]->getX();
            int y = _playersArray[i]->getY();
            map[y][x] = std::to_string(i + 1)[0];
        }
    }
}