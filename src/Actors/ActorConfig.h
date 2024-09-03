#pragma once

#include <map>
#include <string>

#include "Physics/Vec2.h"
#include "Actors/ActorTypes.h"

namespace Actors
{
	class ActorConfig
	{
	public:
		inline static const std::map<ActorTypes, std::string> imageName = {
			{ActorTypes::PLAYER, "PlayerSheet"}
		};

		inline static const std::map<ActorTypes, Physics::Vec2f> spriteWidth = {
			{ActorTypes::PLAYER, Physics::Vec2f(128, 128)}
		};
	};

}