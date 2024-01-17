#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Actors/ActorComponents.h"
#include "Assets/TextureDict.h"

namespace Actors
{
	class ActorFactory
	{
	public:
		static void buildGraphicsComponent(
			const ActorTypeComponent& types, ActorGraphicsComponent& graphics
		);
		
		static void ActorFactory::buildTransformComponent(
			const ActorTypeComponent& types,
			ActorTransformComponent& transform,
			float relativeLength
			);

		static void buildCollisionComponent(
			const ActorTypeComponent& types, 
			const ActorTransformComponent& transform,
			ActorCollisionComponent& collision
		);
		
	};

}

