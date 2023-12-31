#include "Actors/ActorEntityManager.h"

namespace Actors
{
	void ActorEntityManager::renderActors(sf::RenderWindow& window)
	{
		for (const ActorGraphicsComponent& graphics : graphicsComponents)
		{
			if (graphics.isVisible)
			{
				window.draw(graphics.sprite);
			}
		}
	}

	void ActorEntityManager::updateActors(float deltaTime)
	{
		for (const ActorEntity& actor : entities)
		{
			if (actor.isAssigned)
			{
				ActorForceComponent& forces = forceComponents[actor.id];
				ActorTransformComponent& transform = transformComponents[actor.id];
				ActorGraphicsComponent& graphics = graphicsComponents[actor.id];

				transform.position.x += deltaTime * forces.netForce.x;
				transform.position.y += deltaTime * forces.netForce.y;

				forces.netForce = Physics::Vec2f(0.f, 0.f);

				graphics.sprite.setPosition(
					transform.position.x,
					transform.position.y
				);
			}
		}
	}

	void ActorEntityManager::assignActor(std::string type, std::string subtype)
	{
		int id = 0;
		while (id < entities.size())
		{
			if (!entities[id].isAssigned)
			{
				entities[id].isAssigned = true;
				typeComponents[id].type = type;
				typeComponents[id].subtype = subtype;
				graphicsComponents[id].isVisible = true;
				
				m_totalActors += 1;
				id += 1;
				break;
			}
		}
	}

	void ActorEntityManager::unassignActor(int id)
	{
		entities[id].isAssigned = false;
		graphicsComponents[id].isVisible = false;
		m_totalActors -= 1;
	}

	ActorEntityManager::ActorEntityManager()
	{
		m_totalActors = 0;
		m_resizeVectors(10);
	}

	ActorEntityManager::~ActorEntityManager()
	{
		
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
}