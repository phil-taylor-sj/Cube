#pragma once

#include <SFML/Graphics.hpp>
#include "Physics/Vec2.h"
#include "Physics/Rectangle.h"
#include "Physics/Circle.h"

namespace Actors
{
	struct ActorGraphicsComponent
	{
		sf::Sprite sprite;
		bool isVisible = true;
	};

	struct ActorTypeComponent
	{
		std::string type = "None";
		std::string subtype = "None";
	};

	struct ActorTransformComponent
	{
		Physics::Vec2f position;
		float angle;
	};

	struct ActorForceComponent
	{
		Physics::Vec2f netForce;
		float weight = 75.f;
		float movement = 75.f;
		float movementAngle = 0.f;
	};

	struct ActorCollisionComponent
	{
		Physics::Rectangle rectangle;
		Physics::Circle broadCircle;
		float relativeBroadRadius;
	};
}