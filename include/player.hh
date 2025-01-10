#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player(int x, int y, short int id, short int victory, std::string orientation, short int life = 10, short int energy = 2, short int color = 0);

        short int getId();
        void setId(short int id);

        short int getVictory();
        void setVictory(short int victory);

        std::string getOrientation();
        void setOrientation(std::string orientation);

        short int getLife();
        void setLife(short int life);

        short int getEnergy();
        void setEnergy(short int energy);

        int getX();
        void setX(int x);
        
        int getY();
        void setY(int y);

        short int getColor();
        void setColor(short int color);

        sf::Sprite sprite;
        int r;
        int g;
        int b;
        std::vector<std::string> actions = {};
    private:
        short int id;
        short int life;
        short int energy;
        short int victory;
        int x;
        int y;
        short int color;
        std::string orientation;
        
};
