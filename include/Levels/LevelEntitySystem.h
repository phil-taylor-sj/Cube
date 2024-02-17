#pragma once

#include "Levels/DetectedLevelCollisions.h"
#include "Levels/CellComponents.h"
#include "Physics/Physics.h"
#include "Actors/Actors.h"
#include "Levels/LevelEntityManager.h"
#include "Levels/LevelMoveAction.h"


namespace Levels
{
	class LevelEntitySystem
	{
	public:
		static void getWallCollisions(
			DetectedLevelCollisions& detectedCollisions,
			const CellCollisionComponent& cellCollision,
			const Physics::CircleParams& actorCircle
		);

		static void getFloorCollisions(
			DetectedLevelCollisions& detectedCollisions,
			const CellCollisionComponent& cellCollision,
			const CellForceComponent& cellForce,
			const Physics::CircleParams& actorCircle
			);


		static void createMoveAction(
			int axis,
			std::vector<std::vector<int>>& cellGrid,
			std::vector<CellMoveComponent>& moveComponents,
			std::vector<LevelMoveAction>& moveActions
		);

		static void adjustGravityMotion(CellGravityComponent& gravity);

		static void applyMovement(
			CellMoveComponent& move, CellTransformComponent& transform,
			CellForceComponent& force, float relativeSpeed, float commonCellWidth
		);

		static void updateCellIndicies(
			const std::vector<std::vector<int>>& cellGrid,
			std::vector<CellTransformComponent>& transformComponents,
			std::vector<CellMoveComponent>& moveComponents,
			int startIndex, int endIndex
		);

	};
}