#pragma once

#include <string>
#include <SFML/Network.hpp>
#include <random>

class Client {
   public:
   Client(int port):port(port){};
   void run();

   void searchCommand(std::string mapResponse, std::string &command, std::string &nextCommand);

   int generateRandNum(int min, int max);

   void displayResponse(std::string response);

   bool getArguments(int argc, char **argv);

   private:
   sf::TcpSocket sk;
   int port;
};