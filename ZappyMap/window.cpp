#include "SFML/Graphics.hpp"
#include "window.hh"


void Game::initGame() {
    std::cout << map_width << std::endl;
    renderWindow = new sf::RenderWindow(sf::VideoMode(map_width*100+60, map_height*100+60), "Zappy Game");
}
void Game::displayMap(char **map) {
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            std::cout << "|" << map[i][j] << "|";
        }
        std::cout << std::endl;
    }
}
void Game::draw(std::vector<Player*> playersArray, char **map) {
    
    texture.loadFromFile("../../ZappyMap/images/tile.png");
    sf::Sprite sprite(texture);
    std::vector<sf::Sprite> tiles;
    std::vector<sf::Sprite> Gems;
    for (int i = 0; i < map_width; i++) {
        for (int j = 0; j < map_height; j++) {
            sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
            sprite.setPosition(sf::Vector2f(30 + 100*i, 30 + 100*j));
            tiles.push_back(sprite);
        }
    }
    
    
    

    // Yellow Gem generate
    
    for(int x = 0; x < map_width; x++) {
        for(int y = 0; y < map_height; y++) {
            if(map[y][x] == 'L') {
                textYellow.loadFromFile("../../ZappyMap/images/yellow.png");
                sf::Sprite spriteYellow(textYellow);
                spriteYellow.setTextureRect(sf::IntRect(0, 0, 50, 50));
                spriteYellow.setPosition(sf::Vector2f(55 + 100 * x, 55 + 100 * y));
                Gems.push_back(spriteYellow);
            }
            else if(map[y][x] == 'M') {
                // Red Gem generate
                textRed.loadFromFile("../../ZappyMap/images/red.png");
                sf::Sprite spriteRed(textRed);
                spriteRed.setTextureRect(sf::IntRect(0, 0, 50, 50));
                spriteRed.setPosition(sf::Vector2f(55 + 100 * x, 55 + 100 * y));
                Gems.push_back(spriteRed);
            }
            else if(map[y][x] == 'D') {
                // Blue Gem generate
                textBlue.loadFromFile("../../ZappyMap/images/blue.png");
                sf::Sprite spriteBlue(textBlue);
                spriteBlue.setTextureRect(sf::IntRect(0, 0, 50, 50));
                spriteBlue.setPosition(sf::Vector2f(55 + 100 * x, 55 + 100 * y));
                Gems.push_back(spriteBlue);
            }
            else if(map[y][x] == 'S') {
                textGreen.loadFromFile("../../ZappyMap/images/green.png");
                sf::Sprite spriteGreen(textGreen);
                spriteGreen.setTextureRect(sf::IntRect(0, 0, 50, 50));
                spriteGreen.setPosition(sf::Vector2f(55 + 100 * x, 55 + 100 * y));
                Gems.push_back(spriteGreen);
            }
        }
    }

    // Players generate
    textureSheet.loadFromFile("../../ZappyMap/images/player.png");
    sf::Sprite spritePlayer(textureSheet);
    for (size_t i = 0; i < playersArray.size(); i++) {
        if (!playersArray.at(i)) {
            continue;;
        }
        spritePlayer.setTextureRect(sf::IntRect(0, 0, 100, 100));
        spritePlayer.setPosition(sf::Vector2f(30 + 100*playersArray[i]->getX(), 30 + 100*playersArray[i]->getY()));
        if (playersArray[i]->getOrientation() == "North") {
            spritePlayer.setTextureRect(sf::IntRect(0, 200, 100, 100));
        } else if (playersArray[i]->getOrientation() == "South") {
            spritePlayer.setTextureRect(sf::IntRect(0, 0, 100, 100));
        } else if (playersArray[i]->getOrientation() == "West") {
            spritePlayer.setTextureRect(sf::IntRect(0, 100, 100, 100));
        } else if (playersArray[i]->getOrientation() == "East") {
            spritePlayer.setTextureRect(sf::IntRect(0, 300, 100, 100));
        }

        // Color random by Player::color
        short int playerColor;
        playerColor = playersArray[i]->getColor();
        if (playerColor == 0) {
            playersArray[i]->r = rand() % 255;
            playersArray[i]->g = rand() % 255;
            playersArray[i]->b = rand() % 255;
            //std::cout << randNum1<<randNum2<<randNum3 << std::endl;
            playersArray[i]->setColor(1);
        }
        
        spritePlayer.setColor(sf::Color(playersArray[i]->r, playersArray[i]->g, playersArray[i]->b));
        // if (playerColor == 2) {
        //     spritePlayer.setColor(sf::Color(255,0,0));
        // } else if (playerColor == 3) {
        //     spritePlayer.setColor(sf::Color(0,0,255));
        // } else if (playerColor == 4) {
        //     spritePlayer.setColor(sf::Color(0,0,0));
        // }
        
        playersArray[i]->sprite = spritePlayer;
        renderWindow->draw(spritePlayer);
    }

    // Clear and draw all textures
    renderWindow->clear();
    for (size_t i = 0; i < tiles.size(); i++) {
        renderWindow->draw(tiles[i]);
    }
    for (size_t i = 0; i < Gems.size(); i++) {
        renderWindow->draw(Gems[i]);
    }
    for (size_t i = 0; i < playersArray.size(); i++) {
        if (!playersArray.at(i)) {
            continue;;
        }
        renderWindow->draw(playersArray[i]->sprite);
    }
    renderWindow->display();
}

void Game::event() {
    while (renderWindow->pollEvent(this->ev))
        {
            if (this->ev.type == sf::Event::EventType::Closed)
                renderWindow->close();
        }
}