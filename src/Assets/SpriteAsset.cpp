#include "Assets/SpriteAsset.h"


sf::Vector2f SpriteAsset::getPosition()
{
	return _position;
}

void SpriteAsset::scaleSprite(float scaleFactor)
{
	_sprite.setScale(scaleFactor, scaleFactor);
}

void SpriteAsset::drawSprite(sf::RenderWindow& window)
{
	window.draw(_sprite);
}

SpriteAsset::SpriteAsset()
{
	_position.x = 0.0;
	_position.y = 0.0;
}

SpriteAsset::~SpriteAsset()
{

}