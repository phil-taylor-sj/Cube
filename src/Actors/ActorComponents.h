#pragma once

#include <SFML/Graphics.hpp>
#include "Physics/Vec2.h"
#include "Physics/Rectangle.h"
#include "Physics/Circle.h"
#include "Actors/ActorTypes.h"

namespace Actors
{
	class ActorComponentTypes
	{
	public:
		static enum
		{
			GRAPHICS,
			TYPE,
			TRANSFORM,
			FORCE,
			COLLISION,
			GRAVITY
		};
	};

	struct ActorGraphicsComponent
	{
		sf::Sprite sprite;
		bool isVisible = true;
		bool isBackground = false;
		float initialTextureAngle = 0.f;
	};

	struct ActorTypeComponent
	{
		ActorTypes type = ActorTypes::NONE;
		ActorSubtypes subtype = ActorSubtypes::NONE;
	};

	struct ActorTransformComponent
	{
		Physics::Vec2f position;
		float angle;
		float width = 1.f;
		float height = 1.f;
		float relativeWidth = 1.f;
		float relativeHeight = 1.f;
	};

	struct ActorForceComponent
	{
		Physics::Vec2f netForce;
		bool isMoving = true;
		float weight = 75.f;
		float movement = 75.f;
		float movementAngle = 0.f;
	};

	struct ActorCollisionComponent
	{
		Physics::Rectangle rectangle;
		Physics::Circle broadCircle;
		float relativeBroadRadius = 1.f;
	};

	struct ActorGravityComponent
	{
		static enum State
		{
			STEADY,
			FALLING,
			VANISHED
		};

		float timer = 0.f;
		State ActorState = STEADY;
		float currentScale = 1.f;
		float verticalTime = 3.f;
	};
}