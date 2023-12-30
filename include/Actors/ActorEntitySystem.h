#pragma once
#include "math.h"
#include "Physics/Vec2.h"
#include "Actors/ActorComponents.h"
#include "Actors/ActorEntity.h"

namespace Actors
{
	class ActorEntitySystem
	{
		static void applyMovementForce(std::vector<ActorForceComponent>& forceComponents);
	};
}