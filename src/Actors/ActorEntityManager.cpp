#include "Actors/ActorEntityManager.h"

namespace Actors
{
	void ActorEntityManager::renderActors(sf::RenderWindow& window)
	{
		window.draw(graphicsComponents[0].sprite);
		for (const ActorGraphicsComponent& graphics : graphicsComponents)
		{
			if (graphics.isVisible)
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
				ActorForceComponent& forces = forceComponents[actor.id];
				ActorTransformComponent& transform = transformComponents[actor.id];
				ActorCollisionComponent& collision = collisionComponents[actor.id];

				transform.position.x += deltaTime * forces.netForce.x;
				transform.position.y += deltaTime * forces.netForce.y;

				forces.netForce = Physics::Vec2f(0.f, 0.f);

				collision.broadCircle.setPosition(transform.position);
				collision.rectangle.setPosition(transform.position);
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
		}
	}

	void ActorEntityManager::assignActor(ActorTypes type, ActorSubtypes subtype)
	{
		int id = m_findFreeEntity();
		if (id >= 0)
		{
			entities[id].isAssigned = true;
			typeComponents[id].type = type;
			typeComponents[id].subtype = subtype;
			graphicsComponents[id].isVisible = true;
			
			ActorFactory::buildGraphicsComponent(typeComponents[id], graphicsComponents[id]);
			
			ActorFactory::buildTransformComponent(
				typeComponents[id], 
				transformComponents[id], 
				m_referenceLength
			);
			
			ActorFactory::buildCollisionComponent(
				typeComponents[id], 
				transformComponents[id], 
				collisionComponents[id]
			);
			
			m_totalActors += 1;			
		}
	}

	void ActorEntityManager::unassignActor(int id)
	{
		entities[id].isAssigned = false;
		graphicsComponents[id].isVisible = false;
		forceComponents[id].isMoving = false;
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
	}

	void ActorEntityManager::m_loadAllTextures()
	{
		std::array<std::string, 1> texturesToLoad
		{
			"PlayerPlaceholder"
		};

		for (std::string name : texturesToLoad)
		{
			Assets::TextureDict::getInstance()->loadTexture(name);
		}
	}
}