#ifndef window
#define window
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Zappy/player/player.hh"

class Game{
    public:
        Game(int map_width, int map_height)
        :map_width(map_width), map_height(map_height), renderWindow(nullptr)
        {
            this->initGame();
        };
        int map_width;
        int map_height;
        sf::RenderWindow *renderWindow;
        sf::Texture textYellow;
        sf::Texture textRed;
        sf::Texture textBlue;
        sf::Texture textGreen;
        sf::Texture texture;
        sf::Texture textureSheet;

        sf::Event ev;
        
        void initGame();
        void displayMap(char **map);
        void draw(std::vector<Player*> playersArray, char **map);
        void event();
};


#endif // et rien après