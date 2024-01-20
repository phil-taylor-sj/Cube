#pragma once
#include <vector>
#include "Physics/Vec2.h"
#include "Physics/Rectangle.h"

namespace Levels
{
	struct DetectedLevelCollisions	
	{
		std::vector<Physics::RectParams> wallCollisions;
		bool isFloorDetected = false;
		Physics::Vec2f floorForce = Physics::Vec2f(0.f, 0.f);
	};
};