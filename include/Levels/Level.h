/* 
Class: Level

Inheritence: None

Description:
	- Each level consists of a gridof evenly spaced nodes.
	- Each node is assigned a cell, which is positioned so that its corresponding node
	  lies on its upper left corner
	- The origin of each sprite if located at the centerpoint of its corresponding cell.

Methods:
	Level::setCommonCellWidth();
		- Sets the vertical and horizontal spacing for all nodes in the grid.

	Level::initialiseCells();
		- (Purpose) To correctly configure the cell objects in the grid.
		- Sets the x and y indices of cell object based on its location of its node.
		- Assigns a 'Room' texture to each cell object of a randomised colour, ensuring 
		  that no adjacent colours are identical.
		- Assigns a 'Void' texture to all cell objects on the outer boundayr of the grid.
		- (Note) The x and y position of each cell object is set internally, based upon
		  its indices and the common cell width of the grid.

	Level::displayGrid();
		- Accepts a reference value to a pre-defined render window.
		- Invokes the 'draw' function of each cell object with the supplied reference.

	Level::_loadAllTextures();
		- Invokes the textureDict singleton instance for all required textures.
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
#include "Utilities/GridGen.h"
#include "Engine/TextureDict.h"

namespace Levels
{
	class LevelEntityManager
	{
	public:
		void setCommonCellWidth(float comonCellWidth);
		void constructCells();
		void displayGrid(sf::RenderWindow& window);

		LevelEntityManager(int xNumberOfRooms, int yNumberOfRooms);

	private:
		std::vector<std::vector<CellEntity>>> m_cellEntities;
		std::vector<CellGraphicsComponent> m_cellGraphicsComponents;
		std::vector<CellTransformComponent> m_cellTransformComponents;
		std::vector<CellWallsComponent> m_cellWallsComponents;
		int m_xGridSize;
		int m_yGridSize;
		float m_commonCellWidth;
		void m_loadAllTextures();
	};
}