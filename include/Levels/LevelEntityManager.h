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

#include "Levels/CellComponents.h"
#include "Levels/CellEntity.h"
#include "Utilities/GridGen.h"
#include "Assets/TextureDict.h"
#include "Levels/LevelFactory.h"
#include "Physics/Physics.h"
#include "Actors/ActorComponents.h"


namespace Levels
{
	/**
	 * @class LevelEntityManager
	 * @brief Manages entities and operations related to a game level.
	 */
	class LevelEntityManager
	{
	public:	
		/**
	     * @brief Set the common cell width for all cells in the level.
         * @param commonCellWidth The width of each cell.
         */
		void setCommonCellWidth(float comonCellWidth);

		/**
         * @brief Get the common cell width for all cells in the level.
         * @return The width of each cell.
         */
		float getCommonCellWidth();
		
		/**
         * @brief Get the size of the grid in terms of the number of cells in x and y directions.
         * @return A Physics::Vec2i representing the grid size.
         */
		Physics::Vec2i getGridSize();

		/**
         * @brief Render the level on the provided SFML RenderWindow.
         * @param window The SFML RenderWindow on which to render the level.
         */
		void renderLevel(sf::RenderWindow& window);

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
		std::vector<Physics::RectParams> getCircleCollisions(
			const Actors::ActorCollisionComponent& actorCollision);

		/**
         * @brief Constructor for the LevelEntityManager class.
         * @param xNumberOfRooms The number of rooms in the x-direction.
         * @param yNumberOfRooms The number of rooms in the y-direction.
         */
		LevelEntityManager(int xNumberOfRooms, int yNumberOfRooms);

	private:


		std::vector<std::vector<CellEntity>> m_cellEntities;
		std::vector<CellTypeComponent> m_cellTypeComponents;
		std::vector<CellGraphicsComponent> m_cellGraphicsComponents;
		std::vector<CellTransformComponent> m_cellTransformComponents;
		std::vector<CellCollisionComponent> m_cellCollisionComponents;
		int m_xGridSize;
		int m_yGridSize;
		int m_totalCells;
		float m_commonCellWidth;
	};
}