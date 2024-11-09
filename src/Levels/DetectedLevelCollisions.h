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
		vecp::Vec2f floorForce = vecp::Vec2f(0.f, 0.f);
		vecp::Vec2f voidCentre = vecp::Vec2f(0.f, 0.f);
	
		void append(const DetectedLevelCollisions& collisions);
	};
};