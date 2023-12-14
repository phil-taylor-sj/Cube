#pragma once
#include <SFML/Graphics.hpp>
#include "Collision/Rectangle.h"

namespace Coll = Collision;

class StaticRectangle
{
public:
	void setRelativePosition(float relativeX, float relativeY);
	void setRelativePosition(sf::Vector2f relativePosition);

	void setRelativeDimensions(float relativeWidth, float relativeHeight);
	
	void setAngle(float angle);

	void setCellWidth(float width);
	
	void setCellPosition(float xPosition, float yPosition);
	void setCellPosition(sf::Vector2f position);

	Coll::RectParams getRectangle();

	StaticRectangle();
	~StaticRectangle();

protected:
	void _updateRectangle();
	Coll::Rectangle _rectangle;
	float _cellWidth;
	sf::Vector2f _cellPosition;
	sf::Vector2f _relativePosition;
	float _relativeWidth;
	float _relativeHeight;
	float _angle;
};