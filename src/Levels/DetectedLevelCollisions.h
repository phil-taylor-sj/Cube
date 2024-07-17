#pragma once
#include <vector>
#include <cmath>
#include "Physics/Vec2.h"
#include "Physics/Rectangle.h"
#include "Levels/CellStaticRectangle.h"

namespace Levels
{
	class DetectedLevelCollisions	
	{
	public:
		std::vector<Physics::RectParams> staticWalls;
		std::vector<Physics::RectParams> blockers;
		bool isFloorDetected = false;
		Physics::Vec2f floorForce = Physics::Vec2f(0.f, 0.f);
		Physics::Vec2f voidCentre = Physics::Vec2f(0.f, 0.f);
	
		void append(const DetectedLevelCollisions& collisions);
	};
};