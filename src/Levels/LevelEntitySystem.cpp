#include "Levels/LevelEntitySystem.h"

namespace Levels
{
	void LevelEntitySystem::getWallCollisions(
		DetectedLevelCollisions& detectedCollisions,
		const CellCollisionComponent& cellCollision,
		const Physics::CircleParams& actorCircle
	)
	{
		for (const CellStaticRectangle& wallCollision : cellCollision.staticWalls)
		{
			if (Physics::checkIntersection(wallCollision.getRectangle(), actorCircle))
			{
				detectedCollisions.wallCollisions.push_back(wallCollision.getRectangle());
			}
		}
	}

	void LevelEntitySystem::getFloorCollisions(
		DetectedLevelCollisions& detectedCollisions,
		const CellCollisionComponent& cellCollision,
		const CellForceComponent& cellForce,
		const Physics::CircleParams& actorCircle
	)
	{
		if (cellCollision.isFloorActive)
		{
			
			for (const CellStaticRectangle& floorCollision : cellCollision.staticFloors)
			{
				if (Physics::checkIntersection(
					actorCircle.position,
					floorCollision.getRectangle()
				)
					)
				{
					detectedCollisions.isFloorDetected = true;
					if (cellForce.isMoving)
					{
						detectedCollisions.floorForce += cellForce.netForce;
					}
				}
			}
		}
	}
}