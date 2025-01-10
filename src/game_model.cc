#include "../includes/game_model.hh"
#include <string>
#include <nlohmann/json.hpp>

using namespace nlohmann;

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
Player Model::generatePlayer(int id) {
    auto p = Player(std::rand()%5, std::rand()%5,id,0,"South");
    players_.push_back(p);
    map_.getMap()[p.getY()][p.getX()] = '0' + id;
    return p;
}

void Model::mapUpdate()
{
    for (size_t i = 0; i < players_.size(); i++)
    {
        int x = players_[i].getX();
        int y = players_[i].getY();
        map_.getMap()[y][x] = std::to_string(i + 1)[0];
    }
}


void Model::generateGems()
{
    char mapValues[4] = {'L', 'D', 'S', 'M'};

    int stoneY = std::rand()%map_.getHeight();
    int stoneX = std::rand()%map_.getWidth();

    if (map_.getMap()[stoneY][stoneX] == ' ')
    {
        map_.getMap()[stoneY][stoneX] = mapValues[std::rand()%4];
    }
}

std::string Model::execute(int id, std::string command) {

        json to_send;
        if (command == "me") {
            json me;
            std::cout << "commande" << std::endl;
            me["id"] = std::to_string(id);
            me["life"] = std::to_string(players_[id-1].getLife());
            me["energy"] = std::to_string(players_[id-1].getEnergy());
            me["victory"] = std::to_string(players_[id-1].getVictory());
            me["orientation"] = players_[id-1].getOrientation();
            to_send["me"] = me;


        }
        else if (command == "right")
        {
            to_send[command] = updatePlayerStats(players_[id-1], 1, "right", 0) ? "OK" : "KO";
        }
        else if (command == "left")
        {
            to_send[command] = updatePlayerStats(players_[id-1], 1, "left", 0) ? "OK" : "KO";
        }
        else if (command == "fwd")
        {
            to_send[command] =  updatePlayerStats(players_[id-1], 1, "none", 1) ? "OK" : "KO";
        }
        else if (command == "leftfwd")
        {
            to_send[command] =  updatePlayerStats(players_[id-1], 1, "left", 1) ? "OK" : "KO";
        }
        else if (command == "rightfwd")
        {
            to_send[command] =  updatePlayerStats(players_[id-1], 1, "right", 1) ? "OK" : "KO";
        }
        else if (command == "back")
        {
            to_send[command] =  updatePlayerStats(players_[id-1], 1, "none", -1) ? "OK" : "KO";
        }
        else if (command == "jump")
        {
            to_send[command] =  updatePlayerStats(players_[id-1], 1, "none", 3) ? "OK" : "KO";
        }
        // packet << to_send.dump();
        // packets.push_back(packet);
        std::cout << to_send.dump() << std::endl;
    return to_send.dump();

}

std::vector<Player> &Model::getPlayers() {
    return players_;
}

Map Model::getMap() {
    return map_;
}



void Model::regenerateEnergies() {
    for (auto &p : players_) {
        p.setEnergy(2);
    }
}

bool Model::updatePlayerStats(Player& player, short int energyCost, std::string orientationDirection, int step)
{
    short int currentEnergy = player.getEnergy();
    if (currentEnergy >= energyCost)
    {
        player.setEnergy(currentEnergy - energyCost);
        updatePlayerOrientation(player, orientationDirection);
        return updatePlayerPosition(player, step);
    }
    return false;
}

void Model::updatePlayerOrientation(Player &player, std::string orientationDirection)
{
    std::string currentOrientation = player.getOrientation();
    std::string orientations[4] = {"North", "East", "South", "West"};
    int orientationIndex = getOrientationIndex(currentOrientation);
    if (orientationDirection == "right")
    {
        player.setOrientation(orientations[(orientationIndex + 1) % 4]);
    }
    else if (orientationDirection == "left")
    {
        player.setOrientation(orientations[(orientationIndex - 1 + 4) % 4]);
    }
}

bool Model::checkPlayerAround(int newX, int newY) {
    // for (size_t i = 0; i < players_.size(); i++) {
    //     if (static_cast<int>(i) != id && players_[i].getY() == newY && players_[i].getX() == newX) {
    //         short int currentLife = players_[i].getLife();
    //         std::cout << "Player " << id + 1 << " attacks player " << i + 1 << std::endl;
    //         players_[i].setLife(currentLife - 1);
    //         return true;
    //     }
    // }
    std::vector<char> pos = {'1', '2', '3', '4'};
    if (std::find(pos.begin(),pos.end(),map_.getMap()[newY][newX]) != pos.end()) {
        int id = map_.getMap()[newY][newX];
        short int currentLife = players_[id-1].getLife();
        players_[id-1].setLife(currentLife - 1);
        return true;
    }
    return false;
}

bool Model::updatePlayerPosition(Player& player, int step)
{
    if (!step) {
        return true;
    }
    std::string currentOrientation = player.getOrientation();
    int currentX = player.getX();
    int currentY = player.getY();
    if (currentOrientation == "North") {
        if (currentY - step < 0 || abs(currentY - step) > map_.getHeight()  - 1 || checkPlayerAround(currentX, currentY - step)) {return false;}
        pickUpStone(player.getId(), currentX, currentY - step);
        player.setY(currentY - step);
    } else if (currentOrientation == "East") {
        if (currentX  + step < 0 || abs(currentX + step) > map_.getWidth() - 1 || checkPlayerAround(currentX + step, currentY)) {return false;}
        pickUpStone(player.getId(), currentX + step, currentY);
        player.setX(currentX + step);
    } else if (currentOrientation == "South") {
        if (currentY  + step < 0 || abs(currentY  + step) > map_.getHeight()  - 1 || checkPlayerAround(currentX, currentY + step)) {return false;}
        pickUpStone(player.getId(), currentX, currentY + step);
        player.setY(currentY + step);
    } else if (currentOrientation == "West") {
        if (currentX - step < 0 || abs(currentX - step) > map_.getWidth()  - 1 || checkPlayerAround(currentX - step, currentY)) {return false;}
        pickUpStone(player.getId(), currentX - step, currentY);
        player.setX(currentX - step);
    }
    map_.getMap()[currentY][currentX] = ' ';
    return true;
}

void Model::pickUpStone(short int id,int newX, int newY) {
    for (size_t i = 0; i < gems.size(); i++) {
        if (map_.getMap()[newY][newX] == gems[i]->getName()) {
            gems[i]->applyEffect(players_,id);
            map_.getMap()[newY][newX] = ' ';
            return;
        }
    }
}

std::vector<std::string> Model::getMap(int id, char **map)
{
    std::vector<std::string> returning;
    if (players_[id-1].getOrientation() == "North")
        returning = getMapNorth(players_[id-1].getY(), players_[id-1].getX(), map);
    if (players_[id-1].getOrientation() == "South")
        returning = getMapSouth(players_[id-1].getY(), players_[id-1].getX(), map);
    if (players_[id-1].getOrientation() == "East")
        returning = getMapEast(players_[id-1].getY(), players_[id-1].getX(), map);
    if (players_[id-1].getOrientation() == "West")
        returning = getMapWest(players_[id-1].getY(), players_[id-1].getX(), map);
    return returning;
}
void Model::removePlayer(int id) {
    players_.erase(std::remove_if(players_.begin(), players_.end(),[id](Player p) {return p.getId()==id;}));
}
std::vector<std::string> Model::getMapNorth(int x, int y, char **map)
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
    if (x - 1 >= 0 && y + 1 < getMap().getWidth()) {
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

std::vector<std::string> Model::getMapSouth(int x, int y, char **map)
{
    std::vector<std::string> returning;
    if (x + 1 < getMap().getHeight() && y + 1 < getMap().getWidth()) {
        std::string s(1, map[x+1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 1 < getMap().getHeight()){
        std::string s(1, map[x+1][y]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 1 < getMap().getHeight() && y - 1 >= 0){
        std::string s(1, map[x+1][y-1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 2 < getMap().getHeight()){
        std::string s(1, map[x+2][y]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    return returning;
}

std::vector<std::string> Model::getMapEast(int x, int y, char **map)
{
    std::vector<std::string> returning;
    if (x - 1 >= 0 &&  y + 1 < getMap().getWidth()){
        std::string s(1, map[x-1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (y + 1 < getMap().getWidth()){
        std::string s(1, map[x][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (x + 1 < getMap().getHeight() && y + 1 < getMap().getWidth()){
        std::string s(1, map[x+1][y+1]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    if (y + 2 < getMap().getWidth()){
        std::string s(1, map[x][y+2]);
        returning.push_back(s);
    }
    else
        returning.push_back(" ");
    return returning;
}

std::vector<std::string> Model::getMapWest(int x, int y, char **map)
{
    std::vector<std::string> returning;
    if (x + 1 < getMap().getHeight() && y - 1 >= 0){
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

