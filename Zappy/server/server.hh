#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <random>
#include <set>
#include <string>
#include "../../ZappyMap/window.hh"
#include "../player/player.hh"
#include <vector>
#include "../gemstone/gemstone.hh"
#include <algorithm>

class Server {
    public:
        Server(int _map_height = 7, int _map_width = 5, std::string _host="localhost", short int port=4242, int players = 4, int cycle = 500);
        void run();
        void init();
        void mapInit();
        void gemstonesInit();
        void accept();
        void sendDisconnectMessage(sf::TcpSocket client);
        void playerInit(short int id, sf::TcpSocket* tcpSocket, int x, int y);
        void disconnectClient(sf::TcpSocket *client,  size_t position);
        void receiveFromClientAndSendToAll();
        void displayMap();
        int generateRandNum(int min, int max);
        void generateStone();
        bool move(std::string command, int id);
        void updatePlayerOrientation(short int id, std::string orientationDirection = "none");
        bool updatePlayerPosition(short int id, int step);
        bool updatePlayerStats(short int id, short int energyCost, std::string orientationDirection = "none", int step = 0);
        void mapUpdate();
        bool checkPlayerAround(int id, int newX, int newY);
        void pickUpStone(short int id, int newX, int newY);
        void removeDeadPlayers();
        void executeAction(int idx, std::string command);
        int getWinningPlayer();
        void generateEnergie();
        bool getArguments(int argc, char *argv[]);
        void generateCycle(sf::Clock &timer);
        void displayPlayersInfo();
        void endGame(int id);
        std::vector<std::string> getMap(int x, int y, std::string orientation, char **map);
        void sendMap();
        std::vector<std::string> getMapNorth(int x, int y, char **map);
        std::vector<std::string> getMapSouth(int x, int y, char **map);
        std::vector<std::string> getMapEast(int x, int y, char **map);
        std::vector<std::string> getMapWest(int x, int y, char **map);
        int nbConnected = 0;
        int _turnNb = 0;
    private:
        int _map_height;
        int _map_width;
        std::string _host;
        short int _port;
        int _players;
        int _cycle;
        std::vector<Player*> _playersArray;
        std::vector<sf::TcpSocket*> clients;
        sf::SocketSelector _selector;
        sf::TcpListener _listener;
        std::vector<GemStone*> _gemStonesArray;
        char** map;
};

std::vector<std::string> getMap(int x, int y, std::string orientation, char **map);
std::vector<std::string> getMapNorth(int x, int y, char **map);
std::vector<std::string> getMapSouth(int x, int y, char **map);
std::vector<std::string> getMapEast(int x, int y, char **map);
std::vector<std::string> getMapWest(int x, int y, char **map);