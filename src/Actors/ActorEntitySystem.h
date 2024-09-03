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
		static void setDeltaTime(float deltaTime);
		static void applyMovementForce(std::vector<ActorForceComponent>& forceComponents);
		static void applyWallCollisions(
			ActorTransformComponent& actorTransform,
			ActorCollisionComponent& actorCollision,
			std::vector<Physics::RectParams> walls
		);
		static void applyFloorMovement(
			ActorTransformComponent& actorTransform,
			ActorCollisionComponent& actorCollision,
			Physics::Vec2f floorForce
		);

		static void adjustGravityMotion(
			ActorGravityComponent& gravity,
			ActorTransformComponent& transform
		);

	private:
		static float m_deltaTime;

	};
}