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
		std::vector<ActorGravityComponent> gravityComponents;

		void assignActor(ActorTypes type, ActorSubtypes subtype);
		void unassignActor(int id);
		void moveActors(float deltaTime);
		void updateGraphics();
		void renderActors(sf::RenderWindow& window);
		
		void setReferenceLength(float length);
		void updateReferenceLength(float length);

		ActorEntityManager();
		~ActorEntityManager();

	private:
		float m_referenceLength;
		int m_totalActors;
		int m_maxActors = 100;
		int m_findFreeEntity();
		void m_resizeVectors(int newSize);
		void m_loadAllTextures();
	};
}