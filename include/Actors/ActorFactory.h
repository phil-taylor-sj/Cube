#pragma once
#include <SFML/Graphics.hpp>
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
	};

}

