#pragma once
#include <SFML/System.hpp>
#include <math.h>

namespace Collision
{
	struct CircleComponent {
		float x;
		float y;
		float radius;
	};

	struct RectComponent
	{
		// Absolute position and dimensions.
		float x;
		float y;
		float width 1.f;
		float height = 1.f;
		float halfWidth = 0.5f;
		float halfHeight = 0.5f;
		float angle = 0.f

		// Absolute radius for broad phase collision detection.
		float broadRadius;

		ion, float yPosition)
		{
			this->position = sf::Vector2f(xPosition, yPosition);
		}

		RectComponent(sf::Vector2f position, float width, float height)
		{
			this->position = position;
			this->width = width;
			this->height = height;
			this->halfWidth = 0.5f * height;
			this->halfHeight = 0.5f * width;
			this->broadRadius = 1.5f * std::max(width, height);
		}

		RectComponent(
			float xPosition, float yPosition,
			float width, float height
		)
		{
			this->position = sf::Vector2f(xPosition, yPosition);
			this->width = width;
			this->height = height;
			this->halfWidth = 0.5f * height;
			this->halfHeight = 0.5f * width;
			this->broadRadius = 1.5f * std::max(width, height);
		}
	};
}