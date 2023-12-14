#pragma once
#include <SFML/System.hpp>

namespace Collision
{
	struct RectParams {
		float x;
		float y;
		float width;
		float height;
		float halfWidth;
		float halfHeight;
		float angle;
	};

	class Rectangle
	{
	public:
		void setPosition(sf::Vector2f position);
		void setPosition(float xPosition, float yPosition);
		void setWidth(float width);
		void setHeight(float height);
		void setAngle(float angle);
		void scaleWidthHeight(float scale);

		sf::Vector2f getPosition();
		float getWidth();
		float getHeight();
		float getHalfWidth();
		float getHalfHeight();
		float getAngle();

		struct RectParams getRectangle();

		Rectangle();
		Rectangle(sf::Vector2f position);
		Rectangle(float xPosition, float yPosition);
		Rectangle(sf::Vector2f position, float width, float height);
		Rectangle(
			float xPosition, float yPosition, 
			float width, float height
		);
		~Rectangle();

	private:
		RectParams _params;
	};
}