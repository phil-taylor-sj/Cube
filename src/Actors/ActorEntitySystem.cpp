#include "Actors/ActorEntitySystem.h"

namespace Actors
{
	void ActorEntitySystem::applyMovementForce(std::vector<ActorForceComponent>& forceComponents)
	{
		for (ActorForceComponent& force : forceComponents)
		{
			if (force.isMoving)
			{
				force.netForce.x += force.movement * cos(force.movementAngle * 3.14159f / 180.f);
				force.netForce.y += force.movement * sin(force.movementAngle * 3.14159f / 180.f);
		
			}
		}
		
	}

	void ActorEntitySystem::applyWallCollisions(
		ActorTransformComponent& actorTransform,
		ActorCollisionComponent& actorCollision,
		const std::vector<Physics::RectParams> collidingWalls
	)
	{
		for (const Physics::RectParams& wall : collidingWalls)
		{
			Physics::Vec2f correction =
				Physics::CollisionCorrections::getWallCorrection(
					actorCollision.broadCircle.getCircle(), wall
				);
			actorTransform.position += correction;
		}

		actorCollision.broadCircle.setPosition(actorTransform.position);
		actorCollision.rectangle.setPosition(actorTransform.position);
	}

}