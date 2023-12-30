#pragma once
#include <SFML/Graphics.hpp>
#include "Physics/Vec2.h"
#include "Physics/Circle.h"
#include "Levels/CellStaticWall.h"
#include <array>

namespace Levels
{
	struct CellGraphicsComponent
	{
		sf::Sprite sprite;
		bool isVisible = true;
		float textureRotation = 0.f;
	};

	struct CellTypeComponent
	{
		std::string type = "None";
		std::string subtype = "None";
	};

	struct CellWallRectComponent
	{
		// Absolute position and dimensions.
		Physics::Vec2f position = Physics::Vec2f(0.f, 0.f);
		float width;
		float height;
		float halfWidth;
		float halfHeight;
		float angle = 0.f;

		// Absolute radius for broad phase collision detection.
		float broadRadius = 0.f;

		// Position and dimensions relative to cell width.
		Physics::Vec2f relativePosition = Physics::Vec2f(0.f, 0.f);
		float relativeWidth;
		float relativeHeight;

		// Radius for broad phase collision detection relative to cell width.
		float relativeBroadRadius;
	};

	struct CellCollisionComponent
	{
		std::array<CellStaticWall, 8> staticWalls;
		Physics::Circle broadCircle;
		float relativeBroadRadius;
	};

	struct CellTransformComponent
	{
		Physics::Vec2f position = Physics::Vec2f(0.f, 0.f);
		float cellWidth;
		float rotation;
		Physics::Vec2i cellIndices = Physics::Vec2i(0, 0);

		
	};


}

