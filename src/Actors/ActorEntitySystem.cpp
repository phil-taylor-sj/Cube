#include "Actors/ActorEntitySystem.h"

namespace Actors
{
	void ActorEntitySystem::setDeltaTime(float deltaTime)
	{
		m_deltaTime = deltaTime;
	}

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
			vecp::Vec2f correction =
				Physics::CollisionCorrections::getWallCorrection(
					actorCollision.broadCircle.getCircle(), wall
				);
			actorTransform.position += correction;
		}

		actorCollision.broadCircle.setPosition(actorTransform.position);
		actorCollision.rectangle.setPosition(actorTransform.position);
	}

	void ActorEntitySystem::applyFloorMovement(
		ActorTransformComponent& actorTransform,
		ActorCollisionComponent& actorCollision,
		vecp::Vec2f floorForce
	)
	{
		actorTransform.position += floorForce;
		actorCollision.broadCircle.setPosition(actorTransform.position);
		actorCollision.rectangle.setPosition(actorTransform.position);
	}

	void ActorEntitySystem::adjustGravityMotion(
		ActorGravityComponent& gravity, 
		ActorTransformComponent& transform)
	{
		if (gravity.ActorState == ActorGravityComponent::STEADY)
		{
			return;
		}
		gravity.timer += m_deltaTime;
		//float time = gravity.timer.getElapsedTime().asSeconds();
		float timeFraction = std::min(gravity.timer / gravity.verticalTime, 1.f);

		switch (gravity.ActorState)
		{
		case ActorGravityComponent::FALLING:
			gravity.currentScale = 1.f - pow(timeFraction, 2);
			if (timeFraction == 1.f)
			{
				gravity.ActorState = ActorGravityComponent::VANISHED;
			}
			transform.position += (gravity.voidCentre - transform.position) * 0.004f;

			break;
		case ActorGravityComponent::VANISHED:
			gravity.currentScale = 0.f;
			break;
		default:
			break;
		};
	}

	float Actors::ActorEntitySystem::m_deltaTime = 0.1f;
}