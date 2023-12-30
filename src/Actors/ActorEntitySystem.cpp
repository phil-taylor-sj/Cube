#include "Actors/ActorEntitySystem.h"

namespace Actors
{
	void ActorEntitySystem::applyMovementForce(std::vector<ActorForceComponent>& forceComponents)
	{
		for (ActorForceComponent& force : forceComponents)
		{
			force.netForce.x += force.movement * cos(force.movementAngle * 3.14159f / 180.f);
			force.netForce.y += force.movement * sin(force.movementAngle * 3.14159f / 180.f);
		}
		
	}

}