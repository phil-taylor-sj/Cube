#include <SFML/Graphics.hpp>

struct CellGraphicsComponent
{
	sf::Sprite sprite;
	bool isVisible = true;
};

struct CellWallRectComponent
{
	// Absolute position and dimensions.
	sf::Vector2f position = sf::Vector(0.f, 0.f);
	float width;
	float height;
	float halfWidth;
	float halfHeight;
	float angle = 0.f

	// Absolute radius for broad phase collision detection.
	float broadRadius = 0.f;

	// Position and dimensions relative to cell width.
	sf::Vector2f relativePosition = sf::Vector2f(0.f, 0.f);
	float relativeWidth;
	float relativeHeight;

	// Radius for broad phase collision detection relative to cell width.
	float relativeBroadRadius;
};



struct CellTransformComponent
{
	sf::Vector2f positon = sf::Vector2f(0.f, 0.f);
	float cellWidth;
	float rotation;
};