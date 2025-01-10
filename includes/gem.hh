#include "player.hh"
#include <iostream>

class GemStone
{
    public:
        virtual char getName();
        void setName(char name);
        virtual void applyEffect(std::vector<Player> playersArray, short int id) = 0;
    private:
        char name = 'X';
};

class Linemate: public GemStone
{
    public:
        void applyEffect(std::vector<Player> playersArray, short int id) override;
    private:
        char name = 'L';
};

class Deraumere: public GemStone
{
    public:
        void applyEffect(std::vector<Player> playersArray, short int id) override;
    private:
        char name = 'D';
};

class Sibur: public GemStone
{
    public:
        void applyEffect(std::vector<Player> playersArray, short int id) override;
    private:
        char name = 'S';
};

class Mendiane: public GemStone
{
    public:
        void applyEffect(std::vector<Player> playersArray, short int id) override;
    private:
        char name = 'M';
};
