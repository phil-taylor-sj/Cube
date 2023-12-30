#pragma once
#include "Actors/ActorEntity.h"
#include "Actors/ActorComponents.h"

namespace Actors
{
	class ActorEntityManager
	{
	public:
		
		std::vector<ActorEntity> entities;
		std::vector<ActorTypeComponent> typeComponents;
		std::vector<ActorGraphicsComponent> graphicsComponents;
		std::vector<ActorTransformComponent> transformComponents;
		std::vector<ActorCollisionComponent> collisionComponents;
		std::vector<ActorForceComponent> forceComponents;
		
		void assignActor(std::string type, std::string subtype);
		void unassignActor(int id);
		void updateActors(float deltaTime);
		void renderActors(sf::RenderWindow& window);

		ActorEntityManager();
		~ActorEntityManager();

	private:

		int m_totalActors;
		void m_resizeVectors(int newSize);
	};
}