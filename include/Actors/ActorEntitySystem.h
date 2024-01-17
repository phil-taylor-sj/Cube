#pragma once
#include "math.h"
#include "Physics/Physics.h"
#include "Actors/ActorComponents.h"
#include "Actors/ActorEntity.h"

namespace Actors
{
	class ActorEntitySystem
	{
	public:
		static void applyMovementForce(std::vector<ActorForceComponent>& forceComponents);
		static void applyWallCollisions(
			ActorTransformComponent& actorTransform,
			ActorCollisionComponent& actorCollision,
			std::vector<Physics::RectParams> walls
		);
	};
}