#include "Levels/DetectedLevelCollisions.h"

namespace Levels
{
	void DetectedLevelCollisions::append(const DetectedLevelCollisions& collisions)
	{
		for (const Physics::RectParams& wall : collisions.staticWalls)
		{
			this->staticWalls.push_back(wall);
		}

		if (this->isFloorDetected == false)
		{
			this->isFloorDetected == collisions.isFloorDetected;
		}

		if (collisions.isFloorDetected)
		{
			this->floorForce = collisions.floorForce;
		}
	}
}