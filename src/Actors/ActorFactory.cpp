#include "Actors/ActorFactory.h"

namespace Actors
{
	void ActorFactory::buildGraphicsComponent(
		const ActorTypeComponent& types, ActorGraphicsComponent& graphics
	)
	{
		std::string textureName;
		switch (types.type)
		{
			case ActorTypes::PLAYER:
				textureName = "PlayerSheet";
				break;
			default:
				return;
		}

		std::map<ActorTypes, float> initialTextureAngles
		{
			{ActorTypes::PLAYER, -90.f}
		};

		graphics.sprite.setTexture(
			Assets::TextureDict::getInstance()->getTexture(ActorConfig::imageName.at(types.type))
		);
		graphics.sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));

		graphics.sprite.setOrigin(
			graphics.sprite.getLocalBounds().width * 0.5f,
			graphics.sprite.getLocalBounds().height * 0.5f
		);

		graphics.initialTextureAngle = initialTextureAngles[types.type];
	}

	void ActorFactory::buildTransformComponent(
		const ActorTypeComponent& types,
		ActorTransformComponent& transform,
		float referenceLength
	)
	{
		std::map<ActorTypes, std::array<float, 2>> relativeWidthsHeights
		{
			{ActorTypes::PLAYER, {0.5 * 3 * 2 * 0.0625f, 0.5 * 3 * 2 * 0.0625f}}
		};

		transform.relativeWidth = relativeWidthsHeights[types.type][0];
		transform.relativeHeight = relativeWidthsHeights[types.type][1];
		transform.width = transform.relativeWidth * referenceLength;
		transform.height = transform.relativeHeight * referenceLength;
	}

	void ActorFactory::buildCollisionComponent(
		const ActorTypeComponent& types, 
		const ActorTransformComponent& transform,
		ActorCollisionComponent& collision
	)
	{
		std::map<ActorTypes, float> relativeBroadRadii
		{
			{ActorTypes::PLAYER, 1.f}
		};

		collision.relativeBroadRadius = relativeBroadRadii[ActorTypes::PLAYER];
		collision.broadCircle.setRadius(
		std::max(transform.width, transform.height) * 0.5f * 1/3 *
			collision.relativeBroadRadius
		);
	}

	bool ActorFactory::buildGravityComponent(
		const ActorTypeComponent& types,
		ActorGravityComponent& gravity
	)
	{
		std::set<ActorTypes> flyingTypes = 
		{
			ActorTypes::PROJECTILE
		};


		if (flyingTypes.find(types.type) != flyingTypes.end()) 
		{
			return false;
		}

		gravity.timer = 0.f;
		gravity.ActorState = ActorGravityComponent::STEADY;
		gravity.currentScale = 1.f;
		gravity.verticalTime = 2.f;
		return true;

	}

	bool ActorFactory::buildAnimationComponent(
		const ActorTypeComponent& types,
		ActorAnimationComponent& animation
	)
	{
		std::unique_ptr<ActorDistanceAnimation> ptr = std::make_unique<ActorDistanceAnimation>();
		switch (types.type) {
		case ActorTypes::PLAYER:
			ptr->stride = 1.f; // relative to the room
			ptr->textureBounds = std::vector<std::tuple<float, sf::IntRect>> {
				std::make_tuple<float, sf::IntRect>(0.f, sf::IntRect(0, 0, 128, 128)),
				std::make_tuple<float, sf::IntRect>(0.18f, sf::IntRect(128, 0, 128, 128)),
				std::make_tuple<float, sf::IntRect>(0.36f, sf::IntRect(256, 0, 128, 128)),
				std::make_tuple<float, sf::IntRect>(0.44f, sf::IntRect(0, 128, 128, 128)),
				std::make_tuple<float, sf::IntRect>(0.62f, sf::IntRect(128, 128, 128, 128)),
				std::make_tuple<float, sf::IntRect>(0.80f, sf::IntRect(256, 128, 128, 128))
			};

			ptr->application = ActorTypeComponent::ALIVE;
			animation.animations.push_back(std::move(ptr));
			break;
		default:
			return false;
			break;
		}
		
		return true;

	}
}