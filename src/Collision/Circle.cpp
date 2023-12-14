#include "Collision/Circle.h"

namespace Collision
{
	void Circle::setPosition(sf::Vector2f position)
	{
		_params.x = position.x;
		_params.y = position.y;
	}

	void Circle::setPosition(float xPosition, float yPosition)
	{
		_params.x = xPosition;
		_params.y = yPosition;
	}

	sf::Vector2f Circle::getPosition()
	{
		return sf::Vector2f(_params.x, _params.y);
	}

	void Circle::setRadius(float radius)
	{
		_params.radius = radius;
		_params.radiusSquared = pow(radius,2);
	}

	void Circle::scaleRadius(float scale)
	{
		_params.radius = _params.radius * scale;
		_params.radiusSquared = pow(_params.radius, 2);
	}

	float Circle::getRadius()
	{
		return _params.radius;
	}

	float Circle::getRadiusSquared()
	{
		return _params.radiusSquared;
	}
	CircleParams Circle::getCircle()
	{
		return _params;
	}

	Circle::Circle()
	{
		_params.x = 0.f;
		_params.y = 0.f;
		_params.radius = 1.f;
		_params.radiusSquared = 1.f;
	}


	Circle::Circle(sf::Vector2f position, float radius)
	{
		_params.x = position.x;
		_params.y = position.y;
		_params.radius = radius;
		_params.radiusSquared = pow(radius, 2);
	}

	Circle::Circle(float xPosition, float yPosition, float radius)
	{
		_params.x = xPosition;
		_params.y = yPosition;
		_params.radius = radius;
		_params.radiusSquared = pow(radius, 2);
	}

	Circle::~Circle()
	{

	}
}