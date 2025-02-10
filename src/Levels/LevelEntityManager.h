/**
 * @file LevelEntityManager.h
 * @brief Definition of the Levels::LevelEntityManager class.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <bitset>

#include "Levels/DetectedLevelCollisions.h"
#include "Levels/CellComponents.h"
#include "Levels/CellEntity.h"
#include "Levels/LevelEntitySystem.h"
#include "levels/LevelMoveAction.h"
#include "Utilities/GridGen.h"
#include "Assets/TextureDict.h"
#include "Levels/LevelFactory.h"
#include "Physics/Physics.h"
#include "Actors/ActorComponents.h"


namespace Levels
{
	struct LevelSettings
	{
		float cellWidth{512.f};
		vecp::Vec2i size{4, 4};
	};

	/**
	 * \class LevelEntityManager
	 * \brief Manages entities and operations related to a game level.
	 */
	class LevelEntityManager
	{
	public:

		enum ShiftAxis
		{
			COLUMN = 0,
			ROW = 1
		};

		void updateLevel();


		/**
         * @brief Get the common cell width for all cells in the level.
         * @return The width of each cell.
         */
		float getCommonCellWidth();
		
		/**
         * @brief Get the size of the grid in terms of the number of cells in x and y directions.
         * @return A Physics::Vec2i representing the grid size.
         */
		vecp::Vec2i getGridSize();


		void processLevelShift();

		/**
		 * @brief Render the background texture for the level.
		 * 
		 * This must be called before LevelEntityManager::renderLevel during each draw window.
		 *
		 * @param window The SFML RenderWindow on which to render the level.
		 
		 */
		void renderBackground(sf::RenderWindow& window);

		/**
         * @brief Render the level on the provided SFML RenderWindow.
         * @param window The SFML RenderWindow on which to render the level.
         */
		void renderLevel(sf::RenderWindow& window);

		void clearForces();

		/**
         * @brief Update the scaling of all cell sprites based on their cell width.
         */
		void updateAllCellScaling();

		/**
         * @brief Update the positions of all cell sprites based on their cell transform data.
         */
		void updateAllCellPositions();

		/**
         * @brief Get circle collisions between an actor and cells in the level.
         * @param actorCollision The actor's collision component.
         * @return A vector of Physics::RectParams representing detected collisions.
         */
		DetectedLevelCollisions getCircleCollisions(
			const Actors::ActorCollisionComponent& actorCollision);

		/**
         * @brief Constructor for the LevelEntityManager class.
         * @param xNumberOfRooms The number of rooms in the x-direction.
         * @param yNumberOfRooms The number of rooms in the y-direction.
         */
		LevelEntityManager(LevelSettings settings);

	private:
		ShiftAxis m_currentShiftAxis = ROW;
		std::vector<LevelMoveAction> m_currentMoveActions;

		std::vector<std::vector<int>> m_cellEntityGrid;
		std::vector<CellEntity> m_cellEntities;
		std::vector<CellTypeComponent> m_cellTypeComponents;
		std::vector<CellGraphicsComponent> m_cellGraphicsComponents;
		std::vector<CellTransformComponent> m_cellTransformComponents;
		std::vector<CellCollisionComponent> m_cellCollisionComponents;
		std::vector<CellForceComponent> m_cellForceComponents;
		std::vector<CellMoveComponent> m_cellMoveComponents;
		std::vector<CellGravityComponent> m_cellGravityComponents;
		std::vector<CellNumbersComponent> m_cellNumbersComponents;
		std::vector<CellGraphicsComponent> m_cellPanelsComponents;

		sf::Sprite m_backgroundSprite;
		vecp::Vec2i m_gridSize{4, 4};
		int m_totalCells;
		float m_relativeSpeed = 0.005f;
		float m_commonCellWidth = 512.f;
	
		void m_buildCellNumbers();
		void m_scaleFixedWidthComponents();
	};
}