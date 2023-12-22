#include <SFML/Graphics.hpp>

namespace Collision
{
	struct RectComponent
	{
		// Absolute position and dimensions.
		sf::Vector2f position = sf::Vector(0.f, 0.f);
		float width 1.f;
		float height = 1.f;
		float halfWidth = 0.5f;
		float halfHeight = 0.5f;
		float angle = 0.f

		// Absolute radius for broad phase collision detection.
		float broadRadius;

		RectComponent()
		{

		}

		RectComponent(sf::Vector2f position)
		{
			this.position->position;
		}

		RectComponent(float xPosition, float yPosition)
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
