#pragma once
#include <SFML/Graphics.hpp>
#include "player.hh"
#include <iostream>
#include "map.hh"
class View {
    public:
    View(int height=5, int width=5): height_(height), width_(width), window_(new sf::RenderWindow(sf::VideoMode(800, 800), "Zappy")){};
    sf::RenderWindow& getWindow();
    void draw(std::vector<Player>& playersArray, char **&map);
    void displayMap(char **&map);
    ~View() {
        std::cout<< "DESTROYED";
    }
    private:
    int height_;
    int width_;
    sf::RenderWindow *window_;
    sf::Texture textYellow;
    sf::Texture textRed;
    sf::Texture textBlue;
    sf::Texture textGreen;
    sf::Texture texture;
    sf::Texture textureSheet;


    
};