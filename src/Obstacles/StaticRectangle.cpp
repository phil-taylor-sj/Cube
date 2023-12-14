#include "Obstacles/StaticRectangle.h"

void StaticRectangle::setRelativePosition( float relativeX, float relativeY ) 
{
	_relativePosition = sf::Vector2f(relativeX, relativeY);
}

void StaticRectangle::setRelativePosition(sf::Vector2f relativePosition)
{
	_relativePosition = relativePosition;
}

void StaticRectangle::setRelativeDimensions(float relativeWidth, float relativeHeight)
{
	_relativeWidth = relativeWidth;
	_relativeHeight = relativeHeight;
}

void StaticRectangle::setAngle(float angle)
{
	_rectangle.setAngle(angle);
}

void StaticRectangle::setCellWidth(float width)
{
	_cellWidth = width;
	_updateRectangle();
}

void StaticRectangle::setCellPosition(float xPosition, float yPosition)
{
	_cellPosition = sf::Vector2f(xPosition, yPosition);
	_updateRectangle();
}

void StaticRectangle::setCellPosition(sf::Vector2f position)
{
	_cellPosition = position;
	_updateRectangle();
}

Coll::RectParams StaticRectangle::getRectangle()
{
	return _rectangle.getRectangle();
}

StaticRectangle::StaticRectangle()
{
	_cellWidth = 10.f;
	_cellPosition = sf::Vector2f(10.f, 10.f);
	_relativePosition = sf::Vector2f(0.5f, 0.5f);
	_relativeWidth = 0.1f;
	_relativeHeight = 0.1f;
	_angle = 0.f;
	_updateRectangle();
}

StaticRectangle::~StaticRectangle()
{

}

void StaticRectangle::_updateRectangle()
{
	_rectangle.setPosition(
		_cellPosition.x + _relativePosition.x * _cellWidth,
		_cellPosition.y + _relativePosition.y * _cellWidth
		);
	_rectangle.setWidth(_relativeWidth * _cellWidth);
	_rectangle.setHeight(_relativeHeight * _cellWidth);
}
