#include "../../includes/server.hh"
#include "../../includes/game_controller.hh"
#include <iostream>
#include <memory>
#include <thread>


void Server::accept() {
    if (playerSockets_.size() == 1)return;
    if (selector.wait(sf::microseconds(1.0f))) {
        if (selector.isReady(listener_)){
            auto tcpSocket =  std::make_shared<sf::TcpSocket>();
            tcpSocket->setBlocking(false);
            listener_.accept(*tcpSocket);
            selector.add(*tcpSocket);
            for (auto i = 0; i < 1; i++) {
                if (playerSockets_.find(i+1) == playerSockets_.end()) {
                    playerSockets_.insert(std::pair<int, std::shared_ptr<sf::TcpSocket>>(i+1,tcpSocket));
                    controller_.getModel().generatePlayer(i+1);
                    std::cout <<std::to_string(playerSockets_.size())<< std::endl;
                    break;
                }
            }
            std::cout <<"Client accepted"<< std::endl;
        }
    }

}
GameController& Server::getGameController() {
    return controller_;
}
void Server::run() {
    sf::Event event;
    sf::Clock clock;
    auto view = controller_.getView();
    auto &model = controller_.getModel();
    while (view.getWindow().isOpen() ) {
        while (view.getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                view.getWindow().close();
        }
        std::cout <<"test" << model.players_.size() << std::endl;
        if (model.getPlayers().size() < 1) {

            accept();
        }
        else {
            sendMap();
            receive();
            if (playerSockets_.size() == 1 && clock.getElapsedTime() < sf::milliseconds(delay_)) std::this_thread::sleep_for(std::chrono::milliseconds((sf::milliseconds(delay_) - clock.getElapsedTime()).asMilliseconds()));
            model.generateGems();
        }

        clock.restart();
        controller_.update_view();
        controller_.getView().displayMap(controller_.getModel().getMap().getMap());
        model.regenerateEnergies();
    }
}

void Server::addPlayer(std::shared_ptr<sf::TcpSocket> socket) {
    for (int i = 0; i < 1; ++i) {
        if (playerSockets_.find(i+1) == playerSockets_.end()) {
            playerSockets_[i+1] = socket;
        }
    }
}


void Server::sendMap() {
    auto players = controller_.getModel().getPlayers();
    for (auto id = 1; id < 2; id++) {
        sf::Packet sendPacket;
        json response;
        auto mapping = controller_.getModel().getMap(id, controller_.getModel().getMap().getMap());
        response["map"] = mapping;
        sendPacket << response.dump();
        playerSockets_[id]->send(sendPacket);

    }
}

void Server::receive() {
    if (playerSockets_.size() != 1) {return;}
    if (selector.wait(sf::microseconds(1.0f)))
    {
        for (auto i = 0; i < 1; i++)
        {
            auto s = playerSockets_[i+1];
            if (selector.isReady(*s))
            {
                sf::Packet receivePacket;
                s->setBlocking(false);
                if (s->receive(receivePacket) == sf::Socket::Done)
                {
                    std::string command;
                    receivePacket >> command;
                    receivePacket.clear();
                    std::string res = controller_.apply_action(i+1, command);
                }
                if (s->receive(receivePacket) == sf::Socket::Disconnected)
                {
                    selector.remove(*s);
                    playerSockets_.erase(i+1);
                    controller_.getModel().removePlayer(i+1);

                }
            }
        }
    }
}
