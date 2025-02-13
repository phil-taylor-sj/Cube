#pragma once
#include <SFML/Graphics.hpp>
#include "Physics/Vec2.h"
#include "Physics/Circle.h"
#include "Levels/CellStaticRectangle.h"
#include "Levels/CellTypes.h"
#include <array>

namespace Levels
{
	enum class CellPanel
	{
		TOP_LEFT,
		TOP_MID,
		TOP_RIGHT,
		MID_LEFT,
		MID_MID,
		MID_RIGHT,
		BOT_LEFT,
		BOT_MID,
		BOT_RIGHT
	};

	class CellComponentTypes
	{
	public:
		static enum
		{
		TYPE,
		GRAPHICS,
		TRANSFORM,
		COLLISION,
		NUMBERS,
		PANELS,
		FORCE,
		MOVE,
		};
	};

	struct CellGraphicsComponent
	{
		sf::Sprite sprite;
		bool isVisible = true;
		bool isBackground = true;
		float textureRotation = 0.f;
	};

	struct CellTypeComponent
	{
		CellTypes type = CellTypes::NONE;
		CellSubtypes subtype = CellSubtypes::NONE;
		CellColours colour = CellColours::NONE;
	};

	/*
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
	*/

	struct CellCollisionComponent
	{
		std::array<CellStaticRectangle, 8> staticWalls;
		std::vector<CellStaticRectangle> staticFloors;
		CellStaticRectangle blocker;

		std::vector<CellStaticRectangle> sensors{2};

		Physics::Circle broadCircle;
		float relativeBroadRadius;
		bool isBlocked = false;
		bool isFloorActive = true;
		bool areCollisionsActive = true;
	};

	struct CellTransformComponent
	{
		vecp::Vec2f position = vecp::Vec2f(0.f, 0.f);
		float cellWidth;
		float rotation;
		vecp::Vec2i cellIndices = vecp::Vec2i(0, 0);
	};

	struct CellForceComponent
	{
		vecp::Vec2f netForce;
		bool isMoving = true;
		float movement = 75.f;
	};

	struct CellMoveComponent
	{
		static enum State
		{
			STATIC,
			MOVING_UP,
			MOVING_DOWN,
			MOVING_LEFT,
			MOVING_RIGHT
		};

		State cellState = STATIC;
		vecp::Vec2i destinationIndicies = vecp::Vec2i(0, 0);
	};

	struct CellGravityComponent
	{
		static enum State 
		{
			STEADY,
			FALLING,
			RISING,
			VANISHED
		};

		float timer;
		State CellState = STEADY; 
		float currentScale = 1.f;
		float verticalTime = 3.f;
	};

	struct CellNumbersComponent
	{
		std::vector<std::string> numbers = {"101", "102", "103"};
		sf::RectangleShape panelBackground{sf::Vector2f(1.f, 1.f)};
		bool isActive = true;
		int currentIndex = 0;
		float period = 2.f;
		float timer = 0.f;
		sf::Text text;
		CellPanel currentPanel = CellPanel::TOP_LEFT;
		vecp::Vec2f relativePosition = vecp::Vec2f(0.f, 0.f);
	};

	struct CellPanelsComponent
	{
		
	};

	struct CellTrapComponent
	{
		bool isTrapped = false;
		bool isActive = false;
	};
}

