#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include <random>
#include <set>

class Client {
    public: 
        Client(std::string host="localhost", short int port=4242);
        void connect();
        std::string prevCommand;
        int generateRandNum(int min, int max);
        void searchCommand(std::string map, std::string& command, std::string& nextCommand);
        bool getArguments(int argc, char **argv);
        void displayResponse(std::string response);
    private:
        std::string _host;
        short int _port;
};
