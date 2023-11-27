#pragma once
#include <SFML/System.hpp>
#include <math.h>

namespace Collision
{
	struct CircleParams {
		float x;
		float y;
		float radius;
		float radiusSquared;
	};

	class Circle
	{
	public:
		void setPosition(sf::Vector2f position);
		void setPosition(float xPosition, float yPosition);
		void setRadius(float radius);
		void scaleRadius(float scale);
		
		float getRadius();
		float getRadiusSquared();
		sf::Vector2f getPosition();

		struct CircleParams getCircle();

		Circle();
		Circle(sf::Vector2f position, float radius);
		Circle(float xPosition, float yPosition, float radius);
		~Circle();

	private:
		CircleParams _params;
	};
}