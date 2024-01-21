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

	void LevelEntitySystem::adjustGravityMotion(CellGravityComponent& gravity)
	{
		if (gravity.CellState == CellGravityComponent::STEADY)
		{
			return;
		}
		float time = gravity.timer.getElapsedTime().asSeconds();
		float timeFraction = std::max(time/gravity.verticalTime, 1.f);

		switch (gravity.CellState)
		{
		case CellGravityComponent::FALLING:
			gravity.currentScale = 1.f - pow(timeFraction, 2);
			if (timeFraction == 1.f)
			{
				gravity.CellState = CellGravityComponent::VANISHED;
			}
			break;
		case CellGravityComponent::RISING:
			gravity.currentScale = pow(timeFraction, 2);
			if (timeFraction == 1.f)
			{
				gravity.currentScale = 1.f;
				gravity.CellState = CellGravityComponent::STEADY;
			}
			break;
		case CellGravityComponent::VANISHED:
			gravity.currentScale = 0.f;
			break;
		default:
			break;
		};
		

	}
	


}