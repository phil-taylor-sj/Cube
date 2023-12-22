#include "Collision/Rectangle.h"


namespace Collision
{
	void Rectangle::setPosition(sf::Vector2f position)
	{
		_params.x = position.x;
		_params.y = position.y;
	}

	void Rectangle::setPosition(float xPosition, float yPosition)
	{
		_params.x = xPosition;
		_params.y = yPosition;
	}

	void Rectangle::setWidth(float width)
	{
		_params.width = width;
		_params.halfWidth = 0.5 * width;
	}

	void Rectangle::setHeight(float height)
	{
		_params.height = height;
		_params.halfHeight = 0.5 * height;
	}

	void Rectangle::setAngle(float angle)
	{
		_params.angle = angle;
	}

	void Rectangle::scaleWidthHeight(float scale)
	{
		_params.width = _params.width * scale;
		_params.height = _params.height * scale;
		_params.halfWidth = 0.5f * _params.width;
		_params.halfHeight = 0.5f * _params.height;
	}

	sf::Vector2f Rectangle::getPosition()
	{
		return sf::Vector2f(_params.x, _params.y);
	}

	float Rectangle::getWidth()
	{
		return _params.width;
	}

	float Rectangle::getHeight()
	{
		return _params.height;
	}

	float Rectangle::getHalfWidth()
	{
		return _params.halfWidth;
	}

	float Rectangle::getHalfHeight()
	{
		return _params.halfHeight;
	}

	float Rectangle::getAngle()
	{
		return _params.angle;
	}

	RectParams Rectangle::getRectangle()
	{
		return _params;
	}

	Rectangle::Rectangle()
	{
		_params.x = 0.f;
		_params.y = 0.f;
		_params.angle = 0.f;
		setWidth(1.f);
		setHeight(1.f);
	}

	Rectangle::Rectangle(sf::Vector2f position)
	{
		_params.x = position.x;
		_params.y = position.y;
		_params.angle = 0.f;
		setWidth(1.f);
		setHeight(1.f);
	}

	Rectangle::Rectangle(float xPosition, float yPosition)
	{
		_params.x = xPosition;
		_params.y = yPosition;
		_params.angle = 0.f;
		setWidth(1.f);
		setHeight(1.f);
	}

	Rectangle::Rectangle(sf::Vector2f position, float width, float height)
	{
		_params.x = position.x;
		_params.y = position.y;
		_params.angle = 0.f;
		setWidth(width);
		setHeight(height);
	}

	Rectangle::Rectangle(
		float xPosition, float yPosition, 
		float width, float height
	)
	{
		_params.x = xPosition;
		_params.y = yPosition;
		_params.angle = 0.f;
		setWidth(width);
		setHeight(height);
	}

	Rectangle::~Rectangle()
	{

	}
}