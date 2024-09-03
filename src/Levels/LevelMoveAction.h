#pragma once
#include "Levels/CellComponents.h"
#include "Assets/TextureDict.h"
#include "Math.h"

namespace Levels
{
	class LevelMoveAction
	{
	public:
		static enum State
		{
			STARTING = 0,
			DROPPING = 1,
			SHIFTING = 2,
			CLIMBING = 3,
			ENDED = 4
		};

		bool hasCountdownCompleted(
			float deltaTime, std::vector<CellGraphicsComponent>& panelsComponents);

		/**
		 * @brief Check if the first cell has vanished before shifting.
		 *
		 * @param gravityComponents A vector of CellGravityComponent objects representing the game grids's move components.
		 * @return True if the first cell has the VANISH gravity state; otherwise, false.
		 */
		bool hasDropCompleted(const std::vector<CellGravityComponent>& gravityComponents) const;

		/**
		 * @brief Check if all remaining cells have completed their movements.
		 *
		 * @param moveComponents A vector of CellMoveComponent objects representing the game grids's move components.
		 * @return True if all remaining cells have the STATIC move state; otherwise, false.
		 */
		bool hasShiftCompleted(const std::vector<CellMoveComponent>& moveComponents) const;
		
		/**
		 * @brief Check if the first cell has finished rising
		 *
         * @param gravityComponents A vector of CellGravityComponent objects representing the game grids's move components.
         * @return True if the first cell has the STEADY gravity state; otherwise, false.
         */
		bool hasRiseCompleted(const std::vector<CellGravityComponent>& gravityComponents) const;

		int getRowOrColumn() const;

		void beginDrop(std::vector<CellGravityComponent>& gravityComponents,
			std::vector<CellCollisionComponent>& collisionComponents);
		void beginShift(std::vector<CellMoveComponent>& moveComponents);
		void beginRise(std::vector<CellGravityComponent>& gravityComponents);
		void endAction(std::vector<CellCollisionComponent>& collisionComponents);

		State getCurrentActionState() const;
		CellMoveComponent::State getShiftAction() const;
		void setDropCellId(int id);
		int getDropCellId();
		
		void addShiftCellId(int id);
		void setShiftAction(CellMoveComponent::State shiftAction);
		
		LevelMoveAction(int rowOrColumn);
		LevelMoveAction(int rowOrColumn, float dropDelay);
		~LevelMoveAction();

	private:
		std::vector<int> m_cellsToShift;
		int m_cellToDrop = 0;
		int m_rowOrColumn = 0;
		float m_dropTimer = 0.f;
		float m_dropDelay = 4.f;
		State m_actionState = STARTING;
		CellMoveComponent::State m_shiftAction = CellMoveComponent::STATIC;
	};
}