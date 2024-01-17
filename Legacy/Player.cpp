#include "Assets/Player.h"

void Player::handleInput()
{
	this->setUpMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)
	);
	this->setDownMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)
	);
	this->setLeftMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	);
	this->setRightMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)
	);
}

Player::Player()
{

}