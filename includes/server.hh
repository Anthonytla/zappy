#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include "game_controller.hh"

class Server
{
    
private:
    short int port;
    sf::SocketSelector selector;
    sf::TcpListener listener_;
    std::unordered_map<int, std::shared_ptr<sf::TcpSocket>> playerSockets_;
    GameController& controller_;
    int delay_;
public:
    Server(short int port, GameController& controller, int delay)
        : port(port), controller_(controller), delay_(delay) {
        listener_.listen(port);
        listener_.setBlocking(false);
        selector.add(listener_);
    };
    void accept();

    GameController& getGameController();

    void run();

    void addPlayer(std::shared_ptr<sf::TcpSocket> socket);

    void receive();
    void sendMap();
};



