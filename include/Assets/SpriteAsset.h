#pragma once
#include <SFML/Graphics.hpp>
#include <array>
class SpriteAsset
{
public:
	void scaleSprite(float scaleFactor);

	sf::Vector2f getPosition();

	void drawSprite(sf::RenderWindow &window);

	SpriteAsset();
	virtual ~SpriteAsset();

protected:
	sf::Vector2f _position;
	sf::Sprite _sprite;
};