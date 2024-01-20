#pragma once

#include "Levels/DetectedLevelCollisions.h"
#include "Levels/CellComponents.h"
#include "Physics/Physics.h"
#include "Actors/Actors.h"
#include "Levels/LevelEntityManager.h"



namespace Levels
{
	class LevelEntitySystem
	{
	public:
		static void getWallCollisions(
			DetectedLevelCollisions& detectedCollisions,
			const CellCollisionComponent& cellCollision,
			const Physics::CircleParams& actorCircle
		);

		static void getFloorCollisions(
			DetectedLevelCollisions& detectedCollisions,
			const CellCollisionComponent& cellCollision,
			const CellForceComponent& cellForce,
			const Physics::CircleParams& actorCircle
			);
	};
}