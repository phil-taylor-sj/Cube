#include "Assets/Character.h"


void Character::setTexture(const sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_sprite.setOrigin(
		_sprite.getLocalBounds().width*0.5,
		_sprite.getLocalBounds().height*0.5
	);
}
void Character::move(float timePeriod)
{
	sf::Vector2f delta = _calculateMovement(timePeriod);
	_position.x += delta.x;
	_position.y += delta.y;
	updatePosition();
}

void Character::setPosition(float xPosition, float yPosition)
{
	_position.x = xPosition;
	_position.y = yPosition;
	_sprite.setPosition(_position);
}

void Character::setRotation(float angle)
{
	_sprite.setRotation(angle);
}

void Character::updatePosition()
{
	_sprite.setPosition(_position);
}


sf::Vector2f Character::_calculateMovement(float timePeriod)
{
	float delta = _movementSpeed * timePeriod;
	float xCoeff = 0.0;
	float yCoeff = 0.0;

	if (_movingUp == true)
	{
		yCoeff = -1.0;
	}
	if (_movingDown == true)
	{
		yCoeff = 1.0;
	}
	if (_movingLeft == true)
	{
		xCoeff = -1.0;
	}
	if (_movingRight == true)
	{
		xCoeff = 1.0;
	}

	float corrector = sqrt(pow(xCoeff, 2) + pow(yCoeff, 2));
	float delta_corrected = 0;
	if (corrector != 0)
	{
		delta_corrected = delta / corrector;
	}
	return sf::Vector2f(
		xCoeff * delta_corrected,
		yCoeff * delta_corrected
	);
}

void Character::setUpMovement(bool order)
{
	_movingUp = order;
	_movingDown = (order == true) ? false : _movingDown;
}
void Character::setDownMovement(bool order)
{
	_movingDown = order;
	_movingUp = (order == true) ? false : _movingUp;
}
void Character::setLeftMovement(bool order)
{
	_movingLeft = order;
	_movingRight = (order == true) ? false : _movingRight;
}
void Character::setRightMovement(bool order)
{
	_movingRight = order;
	_movingLeft = (order == true) ? false : _movingLeft;
}

sf::Vector2f Character::checkMovement(float timePeriod)
{
	sf::Vector2f delta = _calculateMovement(timePeriod);
	return sf::Vector2f(
		_position.x + delta.x,
		_position.y + delta.y
		);
}

void Character::setMovementSpeed(float movementSpeed)
{
	_movementSpeed = movementSpeed;
}

float Character::getMovementSpeed()
{
	return _movementSpeed;
}


Character::Character() 
{
	_movingUp = false;
	_movingDown = false;
	_movingLeft = false;
	_movingRight = false;
	_movementSpeed = 0;
}