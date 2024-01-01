#pragma once
#include <array>
#include "Actors/ActorEntity.h"
#include "Actors/ActorComponents.h"
#include "Actors/ActorTypes.h"
#include "Actors/ActorFactory.h"

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
		
		void assignActor(ActorTypes type, ActorSubtypes subtype);
		void unassignActor(int id);
		void updateActors(float deltaTime);
		void renderActors(sf::RenderWindow& window);

		ActorEntityManager();
		~ActorEntityManager();

	private:

		int m_totalActors;
		int m_maxActors = 100;
		int m_findFreeEntity();
		void m_resizeVectors(int newSize);
		void m_loadAllTextures();
	};
}