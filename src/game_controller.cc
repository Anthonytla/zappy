#include "../includes/game_controller.hh"
#include <SFML/Network.hpp>
#include <string>
#include <nlohmann/json.hpp>

using namespace nlohmann;

// void GameController::run() {
//     auto &window = view_.getWindow();
//     sf::Event event;
//     sf::SocketSelector selector;
//     sf::Packet sendPacket;
//     int id = 0;
//     for (auto &client : clients_) {
//         id++;
//         selector.add(*client);
//         players.push_back(Player(std::rand()%5, std::rand()%5,id,0,"South"));
//     }
//     while (window.isOpen()) {
//         while (window.pollEvent(event))
//         {
//             // "close requested" event: we close the window
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         if (selector.wait(sf::microseconds(1.0f)))
//         {
//             for (size_t i = 0; i < clients_.size(); i++)
//             {
//                 if (clients_.at(i) && selector.isReady(*clients_[i]))
//                 {
//                     sf::Packet receivePacket;
//                     clients_[i]->setBlocking(false);
//                     if (clients_[i]->receive(receivePacket) == sf::Socket::Done)
//                     {
//                         std::string command;
//                         receivePacket >> command;
//                         std::cout<<command<<std::endl;
//                         if (command == "") {return;}
//                         players[i].actions.push_back(command);
                        
//                     }
//                     else if (clients_[i]->receive(receivePacket) == sf::Socket::Disconnected)
//                     {
//                         //this->disconnectClient(clients[i], i);
//                     }
//                 }
//             }

//         }
//         if (players.size() == 2) {
//             window.clear(sf::Color::Black);
//             generatePlayers();
//             generateGems();
//             // view_.displayMap(map_.getMap());
//             view_.draw(players,map_.getMap()); 
//             for (auto p:players) {
//                 sendMap(p.getId());
//             }
//             executeActions();
//             window.display();
//         }


//     }
// }

View& GameController::getView() {
    return view_;
}

Model& GameController::getModel() {
    return model_;
}
// void GameController::executeActions(Player& p) {
//     json to_send;
//     sf::Packet packet;
//         for (auto action : p.actions) {
//             if (action == "me") {
//                 json me;
//                 me["id"] = std::to_string(p.getId());
//                 me["life"] = std::to_string(p.getLife());
//                 me["energy"] = std::to_string(p.getEnergy());
//                 me["victory"] = std::to_string(p.getVictory());
//                 me["orientation"] = p.getOrientation();
//                 to_send["me"] = me;
//                 std::cout << to_send.dump() << std::endl;
//                 packet << to_send.dump();
//             }
//         clients_[p.getId()-1]->send(packet);
// }

// void GameController::sendMap(int id) {
//     // for (size_t i = 0; i < players.size(); i++) {
//         // if (players.at(i))
//         // {
//     sf::Packet sendPacket;
//     int x = players[id-1].getX();
//     int y = players[id-1].getY();
//     std::string orientation = players[id-1].getOrientation();
//     std::vector<std::string> mapping;
//     mapping = getMap(y, x, orientation, map_.getMap());
//     json response;
//     response["map"] = mapping;
//     sendPacket << response.dump();
//     clients_[id-1]->send(sendPacket);
//         // }
//     // } 
// }

// std::vector<std::string> GameController::getMap(int x, int y, std::string orientation, char **map)
// {
//     std::vector<std::string> returning;
//     if (orientation == "North")
//         returning = getMapNorth(x, y, map);
//     if (orientation == "South")
//         returning = getMapSouth(x, y, map);
//     if (orientation == "East")
//         returning = getMapEast(x, y, map);
//     if (orientation == "West")
//         returning = getMapWest(x, y, map);
//     return returning;
// }

// std::vector<std::string> GameController::getMapNorth(int x, int y, char **map)
// {
//     //std::cout << x << y << std::endl;
//     std::vector<std::string> returning;
//     if (x - 1 >= 0 && y - 1 >= 0) {
//     //    std::cout << map[x-1][y-1] << std::endl;
//         std::string s(1, map[x-1][y-1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x - 1 >= 0) {
//     //    std::cout << map[x-1][y] << std::endl;
//         std::string s(1, map[x-1][y]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x - 1 >= 0 && y + 1 < map_.getWidth()) {
//      //   std::cout << map[x-1][y+1] << std::endl;
//         std::string s(1, map[x-1][y+1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x - 2 >= 0) {
//       //  std::cout << map[x-2][y] << std::endl;
//         std::string s(1, map[x-2][y]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     return returning;
// }

// std::vector<std::string> GameController::getMapSouth(int x, int y, char **map)
// {
//     std::vector<std::string> returning;
//     if (x + 1 < map_.getHeight() && y + 1 < map_.getWidth()) {
//         std::string s(1, map[x+1][y+1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x + 1 < map_.getHeight()){
//         std::string s(1, map[x+1][y]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x + 1 < map_.getHeight() && y - 1 >= 0){
//         std::string s(1, map[x+1][y-1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x + 2 < map_.getHeight()){
//         std::string s(1, map[x+2][y]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     return returning;
// }

// std::vector<std::string> GameController::getMapEast(int x, int y, char **map)
// {
//     std::vector<std::string> returning;
//     if (x - 1 >= 0 &&  y + 1 < map_.getWidth()){
//         std::string s(1, map[x-1][y+1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (y + 1 < map_.getWidth()){
//         std::string s(1, map[x][y+1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x + 1 < map_.getHeight() && y + 1 < map_.getWidth()){
//         std::string s(1, map[x+1][y+1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (y + 2 < map_.getWidth()){
//         std::string s(1, map[x][y+2]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     return returning;
// }

// std::vector<std::string> GameController::getMapWest(int x, int y, char **map)
// {
//     std::vector<std::string> returning;
//     if (x + 1 < map_.getHeight() && y - 1 >= 0){
//         std::string s(1, map[x+1][y-1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (y - 1 >= 0){
//         std::string s(1, map[x][y - 1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (x - 1 >= 0 && y - 1 >= 0){
//         std::string s(1, map[x - 1][y - 1]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     if (y - 2 >= 0){
//         std::string s(1, map[x][y - 2]);
//         returning.push_back(s);
//     }
//     else
//         returning.push_back(" ");
//     return returning;
// }

std::string GameController::apply_action(int id, std::string command) {
    return model_.execute(id, command);
}

void GameController::update_view() {
    view_.draw(model_.getPlayers(), model_.getMap().getMap());

}