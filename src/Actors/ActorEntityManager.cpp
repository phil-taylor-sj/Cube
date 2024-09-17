#include "Actors/ActorEntityManager.h"

namespace Actors
{
	void ActorEntityManager::renderForegroundActors(sf::RenderWindow& window)
	{
		//window.draw(graphicsComponents[0].sprite);
		for (const ActorGraphicsComponent& graphics : graphicsComponents)
		{
			if (graphics.isVisible && !graphics.isBackground)
			{
				window.draw(graphics.sprite);
			}
		}
	}

	void ActorEntityManager::renderBackgroundActors(sf::RenderWindow& window)
	{
		//window.draw(graphicsComponents[0].sprite);
		for (const ActorGraphicsComponent& graphics : graphicsComponents)
		{
			if (graphics.isVisible && graphics.isBackground)
			{
				window.draw(graphics.sprite);
			}
		}
	}

	void ActorEntityManager::moveActors(float deltaTime)
	{
		for (const ActorEntity& actor : entities)
		{
			if (actor.isAssigned)
			{
				ActorForceComponent& forces = this->forceComponents[actor.id];
				ActorTransformComponent& transform = this->transformComponents[actor.id];
				ActorCollisionComponent& collision = this->collisionComponents[actor.id];

				transform.position.x += deltaTime * forces.netForce.x;
				transform.position.y += deltaTime * forces.netForce.y;

				collision.broadCircle.setPosition(transform.position);
				collision.rectangle.setPosition(transform.position);

				for (std::unique_ptr<ActorBaseAnimation>& animation : animationComponents[actor.id].animations)
				{
					if (ActorDistanceAnimation* derived = dynamic_cast<ActorDistanceAnimation*>(animation.get()))
					{
						derived->distance += deltaTime * forces.netForce.length() / (derived->stride * this->m_referenceLength);
						if (derived->distance >= 1.f) 
						{ 
							derived->distance -= 1.0f; 
							derived->currentIndex = 0;
							derived->update = true;
						}
						else if (derived->currentIndex + 1 != derived->textureBounds.size())
						{
							if (derived->distance >= std::get<0>(derived->textureBounds[derived->currentIndex + 1]))
							{
								derived->currentIndex++;
								derived->update = true;
							}
						}
						if (forces.netForce.length() < 0.0001f) 
						{
							derived->distance = 0.f;
							derived->currentIndex = 0;
							derived->update = true;
						}
					}
				}

				forces.netForce = Physics::Vec2f(0.f, 0.f);
			}
		}
		animateActors();
	}

	void ActorEntityManager::animateActors()
	{
		for (const ActorEntity& actor : entities)
		{
			if (!actor.components.test(ActorComponentTypes::ANIMATION)) { continue; }
			for (std::unique_ptr<ActorBaseAnimation>& animation : animationComponents[actor.id].animations)
			{
				if (animation->application == typeComponents[actor.id].actorState
					&& animation->update == true)
				{
					graphicsComponents[actor.id].sprite.setTextureRect(
						std::get<1>(animation->textureBounds[animation->currentIndex])
					);
					animation->update = false;
				}
			}
		}
	}

	void ActorEntityManager::updateGraphics()
	{
		for (const ActorEntity& actor : entities)
		{
			ActorGraphicsComponent& graphics = graphicsComponents[actor.id];
			ActorTransformComponent& transform = transformComponents[actor.id];
			graphics.sprite.setPosition(
				transform.position.x,
				transform.position.y
			);
			graphics.sprite.setRotation(transform.angle - graphics.initialTextureAngle);

			if (actor.components.test(Actors::ActorComponentTypes::GRAVITY))
			{
				graphics.isBackground = gravityComponents[actor.id].ActorState
					!= ActorGravityComponent::STEADY;
				float currentScale = gravityComponents[actor.id].currentScale;
				float width = transformComponents[actor.id].width * currentScale;
				float height = transformComponents[actor.id].height * currentScale;

				float spriteWidth = graphics.sprite.getLocalBounds().width;
				float spriteHeight = graphics.sprite.getLocalBounds().height;
				graphics.sprite.setScale(
					width / graphics.sprite.getLocalBounds().width,
					height / graphics.sprite.getLocalBounds().height
				);
				int test = 4;
			}
		}
	}

	void ActorEntityManager::assignActor(ActorTypes type, ActorSubtypes subtype)
	{
		int id = m_findFreeEntity();
		if (id >= 0)
		{

			entities[id].isAssigned = true;

			entities[id].components.set(ActorComponentTypes::TYPE);
			typeComponents[id].type = type;
			typeComponents[id].subtype = subtype;
			graphicsComponents[id].isVisible = true;
			
			entities[id].components.set(ActorComponentTypes::GRAPHICS);
			ActorFactory::buildGraphicsComponent(typeComponents[id], graphicsComponents[id]);
			
			entities[id].components.set(ActorComponentTypes::TRANSFORM);
			ActorFactory::buildTransformComponent(
				typeComponents[id], 
				transformComponents[id], 
				m_referenceLength
			);
			
			entities[id].components.set(ActorComponentTypes::COLLISION);
			ActorFactory::buildCollisionComponent(
				typeComponents[id], 
				transformComponents[id], 
				collisionComponents[id]
			);
			
			
			entities[id].components.reset(ActorComponentTypes::GRAVITY);
			if (ActorFactory::buildGravityComponent(
				typeComponents[id], gravityComponents[id]))
			{
				entities[id].components.set(ActorComponentTypes::GRAVITY);
			}

			if (ActorFactory::buildAnimationComponent(
				typeComponents[id], animationComponents[id]))
			{
				entities[id].components.set(ActorComponentTypes::ANIMATION);
			}
			m_totalActors += 1;			
		}
	}

	void ActorEntityManager::unassignActor(int id)
	{
		entities[id].isAssigned = false;
		graphicsComponents[id].isVisible = false;
		forceComponents[id].isMoving = false;
		entities[id].components.reset();
		m_totalActors -= 1;
	}

	void ActorEntityManager::setReferenceLength(float length)
	{
		m_referenceLength = length;
	}

	void ActorEntityManager::updateReferenceLength(float length)
	{
		m_referenceLength = length;
	}

	ActorEntityManager::ActorEntityManager()
	{
		m_totalActors = 0;
		m_resizeVectors(10);
		m_loadAllTextures();
	}

	ActorEntityManager::~ActorEntityManager()
	{
		
	}

	int ActorEntityManager::m_findFreeEntity()
	{
		int id = 0;
		while (id < entities.size())
		{
			if (!entities[id].isAssigned)
			{
				return id;
			}
		}

		if (entities.size() < m_maxActors)
		{
			int currentSize = entities.size();

			int newSize = std::min(currentSize * 2, m_maxActors);
			m_resizeVectors(newSize);
			return currentSize;
		}
		else
		{
			return -1;
		}
	}

	void ActorEntityManager::m_resizeVectors(int newSize)
	{
		entities.resize(newSize);
		typeComponents.resize(newSize);
		graphicsComponents.resize(newSize);
		transformComponents.resize(newSize);
		collisionComponents.resize(newSize);
		forceComponents.resize(newSize);
		gravityComponents.resize(newSize);
		animationComponents.resize(newSize);
	}

	void ActorEntityManager::m_loadAllTextures()
	{
		std::array<std::string, 1> texturesToLoad
		{
			"PlayerPistol"
		};

		for (std::string name : texturesToLoad)
		{
			Assets::TextureDict::getInstance()->loadTexture(name);
		}
	}
}