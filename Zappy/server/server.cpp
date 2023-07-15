#include "server.hh"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Server::Server(int map_height, int map_width, std::string host, short int port, int players, int cycle)
{
    this->_map_height = map_height;
    this->_map_width = map_width;
    this->_host = host;
    this->_port = port;
    this->_players = players;
    this->_cycle = cycle;
}

void Server::run()
{

    Game *game = new Game(_map_width, _map_height);
    this->gemstonesInit();
    this->init();
    this->mapInit();
    sf::Clock timer;
    while (game->renderWindow->isOpen())
    {
        if (_selector.wait(sf::microseconds(1.0f)))
        {
            if (_selector.isReady(this->_listener) && nbConnected < _players && _turnNb == 0)
                this->accept();
            else {
                this->receiveFromClientAndSendToAll();
            }
        }
        if ((nbConnected == _players || _turnNb > 0) && nbConnected > 0){
            generateCycle(timer);
        }
        game->event();
        game->draw(_playersArray, map);
    }
}

void Server::generateCycle(sf::Clock &timer){
   
    if (timer.getElapsedTime().asMilliseconds() >= _cycle) {
        _turnNb++;
        std::cout << "ROUND "<< _turnNb <<" started" << std::endl;
        generateStone();
        generateEnergie();
        for (size_t i = 0; i < _playersArray.size(); i++) {
            if (_playersArray.at(i)) {
                for (auto command :_playersArray[i]->actions) {
                    executeAction(i, command);
                }
                _playersArray[i]->actions.clear();
            }
        }
        this->displayPlayersInfo();
        this->removeDeadPlayers();
        this->mapUpdate();
        int winningPlayerId = this->getWinningPlayer();
        if (winningPlayerId != -1) // Game won ...
        {
            this->endGame(winningPlayerId + 1);
        }
        displayMap();
        sendMap();
        timer.restart();
    }
}

void Server::endGame(int id)
{
    std::cout << "Player " << id << " won the game !" << std::endl;
    if (_playersArray[id - 1]->getVictory() >= 10) {
        for (size_t i = 0; i < _playersArray.size(); i++)
        {
            if (_playersArray.at(i))
            {
                this->disconnectClient(clients[_playersArray[i]->getId()-1], _playersArray[i]->getId()-1);
            }
        }
    }
    else 
    {
        this->disconnectClient(clients[id - 1], id - 1);
    }
}

void Server::generateEnergie()
{
    for (size_t i = 0; i < _playersArray.size(); i++)
    {
        if (_playersArray.at(i))
        {
            _playersArray[i]->setEnergy(2);
        }
    }
}

void Server::init()
{
    _listener.listen(this->_port);
    _listener.setBlocking(false);
    this->_selector.add(_listener);
    for (int i = 0; i < _players; i++)
    {
        _playersArray.push_back(nullptr);
        clients.push_back(nullptr);
    }
}

void Server::accept()
{

    sf::TcpSocket *tcpSocket = new sf::TcpSocket();
    _listener.setBlocking(false);
    tcpSocket->setBlocking(false);
    bool accepted = false;
    _listener.accept(*tcpSocket);
    _selector.add(*tcpSocket);
    int x = generateRandNum(0, _map_width - 1);
    int y = generateRandNum(0, _map_height - 1);
    while (map[y][x] != ' ')
    {
        x = generateRandNum(0, _map_width - 1);
        y = generateRandNum(0, _map_height - 1);
    }

    for (int i = 0; i < _players; i++)
    {
        if (!_playersArray.at(i) && !accepted)
        {
            sf::Packet sendPacket;
            sendPacket << std::to_string(i + 1);
            tcpSocket->send(sendPacket);
            clients.at(i) = tcpSocket;
            playerInit(i+1, tcpSocket, x, y);
            accepted = true;
            nbConnected++;
        }
    }
}

void Server::receiveFromClientAndSendToAll()
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients.at(i) && _selector.isReady(*clients[i]))
        {
            sf::Packet receivePacket;
            clients[i]->setBlocking(false);
            if (clients[i]->receive(receivePacket) == sf::Socket::Done)
            {
                std::string command;
                receivePacket >> command;
                if (command == "") {return;}
                _playersArray[i]->actions.push_back(command);
                
            }
            else if (clients[i]->receive(receivePacket) == sf::Socket::Disconnected)
            {
                this->disconnectClient(clients[i], i);
            }
        }
    }
}

void Server::disconnectClient(sf::TcpSocket *client, size_t position)
{
    _selector.remove(*client);
    client->disconnect();
    delete client;
    clients.at(position) = nullptr;
    map[_playersArray[position]->getY()][_playersArray[position]->getX()] = ' ';
    delete _playersArray.at(position);
    _playersArray.at(position) = nullptr;
    nbConnected--;
}

int Server::generateRandNum(int min, int max)
{
    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

    return gen(rng);
}

bool Server::getArguments(int argc, char *argv[])
{
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "--host") == 0)
        {
            _host = argv[i + 1];
        }
        else if (strcmp(argv[i], "--port") == 0)
        {
            try{
                _port = std::stoi(argv[i + 1]);
            }
            catch(std::invalid_argument& e) {
                std::cout << "Port must be an int" << std::endl;
                return false;
            }
        }
        else if (strcmp(argv[i], "--map-height") == 0)
        {
            try {
                _map_height = std::stoi(argv[i + 1]);
            }
            catch(std::invalid_argument& e) {
                std::cout << "map height must be an int" << std::endl;
                return false;
            }
            if (_map_height <= 0) {
                std::cout << "Height must be positive" << std::endl;
                return false;
            }
        }
        else if (strcmp(argv[i], "--map-width") == 0)
        {
            try {
                _map_width = std::stoi(argv[i + 1]);
            }
            catch(std::invalid_argument& e) {
                std::cout << "Width must be an int" << std::endl;
                return false;
            }
            if (_map_width <= 0) {
                std::cout << "Width must be positive" << std::endl;
                return false;
            }
        }
        else if (strcmp(argv[i], "--players") == 0)
        {
            try {
                _players = std::stoi(argv[i + 1]);
            }
            catch(std::invalid_argument& e) {
                std::cout << "Number of players must be an int" << std::endl;
                return false;
            }
            if (_players <= 0) {
                std::cout << "Number of players must be positive" << std::endl;
                return false;
            }
            
        }
        else if (strcmp(argv[i], "--cycle") == 0)
        {
            try {
                _cycle = std::stoi(argv[i + 1]);
            }
            catch(std::invalid_argument& e) {
                std::cout << "Duration must be an int" << std::endl;
                return false;
            }
            if (_cycle <= 0) {
                std::cout << "Duration must be positive" << std::endl;
                return false;
            }
        }
    }
    return true;
}