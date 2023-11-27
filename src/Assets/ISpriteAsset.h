#pragma once
#include <SFML/Graphics.hpp>


class ISpriteAsset
{
public:
	virtual void setTexture(const sf::Texture& texture) = 0;
	virtual void setRotation(float angle) = 0;
	virtual void updatePosition() = 0;
};