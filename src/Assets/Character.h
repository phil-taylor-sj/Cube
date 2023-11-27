#pragma once
#include "SpriteAsset.h"
#include "ISpriteAsset.h"
#include <math.h>

class Character : public SpriteAsset, ISpriteAsset
{
public:
	void setTexture(const sf::Texture& texture) override;
	void move(float timePeriod);
	sf::Vector2f checkMovement(float timePeriod);
	void updatePosition() override;
	void setPosition(float xPosition, float yPosition);
	void setRotation(float angle) override;
	void setUpMovement(bool order);
	void setDownMovement(bool order);
	void setLeftMovement(bool order);
	void setRightMovement(bool order);
	void setMovementSpeed(float movementSpeed);
	float getMovementSpeed();
	sf::Vector2f _calculateMovement(float timePeriod);
	Character();

protected:
	float _movementSpeed;
	bool _movingUp;
	bool _movingDown;
	bool _movingLeft;
	bool _movingRight;

};