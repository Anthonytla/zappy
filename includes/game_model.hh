#pragma once
#include "player.hh"
#include "map.hh"
#include "gem.hh"
#include <memory>
#include <nlohmann/json.hpp>

using namespace nlohmann;
class Model {
    public:
    Model(int height=5, int width=5, int nb_players=2): map_(height, width), nb_players_(nb_players), gems({}){
        gems.push_back(std::make_shared<Linemate>());
        gems.push_back(std::make_shared<Deraumere>());
        gems.push_back(std::make_shared<Sibur>());
        gems.push_back(std::make_shared<Mendiane>());
    }

    void regenerateEnergies();

    Player generatePlayer(int id);

    void mapUpdate();

    void generateGems();

    std::string execute(int id, std::string command);
    std::vector<Player>& getPlayers();
    Map getMap();
    bool updatePlayerStats(Player& player, short int energyCost, std::string orientationDirection, int step);
    void updatePlayerOrientation(Player &player, std::string orientationDirection);
    bool updatePlayerPosition(Player& player, int step);
    void pickUpStone(short int id, int newX, int newY);


    std::vector<std::string> getMap(int id, char **map);

    void removePlayer(int id);

    std::vector<std::string> getMapNorth(int x, int y, char **map);

    std::vector<std::string> getMapSouth(int x, int y, char **map);

    std::vector<std::string> getMapEast(int x, int y, char **map);

    std::vector<std::string> getMapWest(int x, int y, char **map);

    bool checkPlayerAround(int newX, int newY);
    std::vector<Player> players_;
    private :


    Map map_;
    int nb_players_;
    std::vector<std::shared_ptr<GemStone>> gems;
    


};