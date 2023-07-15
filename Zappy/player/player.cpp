#include "player.hh"
#include <string>

Player::Player(int x, int y, short int id, short int victory, std::string orientation, sf::TcpSocket *tcpSocket, short int life, short int energy, short int color)
{
    this->id = id;
    this->victory = victory;
    this->orientation = orientation;
    this->life = life;
    this->energy = energy;
    this->tcpSocket = tcpSocket;
    this->x = x;
    this->y = y;
    this->color = color;
}

short int Player::getId()
{
    return this->id;
}

void Player::setId(short int id)
{
    this->id = id;
}

short int Player::getVictory()
{
    return this->victory;
}

void Player::setVictory(short int victory)
{
    this->victory = victory;
}

std::string Player::getOrientation()
{
    return this->orientation;
}

void Player::setOrientation(std::string orientation)
{
    this->orientation = orientation;
}

short int Player::getLife()
{
    return this->life;
}

void Player::setLife(short int life)
{
    this->life = life;
}

short int Player::getEnergy()
{
    return this->energy;
}

void Player::setEnergy(short int energy)
{
    this->energy = energy;
}

sf::TcpSocket* Player::getTcpSocket()
{
    return this->tcpSocket;
}

void Player::setTcpSocket(sf::TcpSocket* tcpSocket)
{
    this->tcpSocket = tcpSocket;
}

int Player::getX() {
    return x;
}

void Player::setX(int x) {
    this->x = x;
}

int Player::getY() {
    return y;
}

void Player::setY(int y) {
    this->y = y;
}

short int Player::getColor() {
    return color;
}

void Player::setColor(short int color) {
    this->color = color;
}