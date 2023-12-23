#include "Levels/Level.h"

namespace::Levels
{
	void LevelEntityManager::setCommonCellWidth(float commonCellWidth)
	{
		_commonCellWidth = commonCellWidth;
	}

	void LevelEntityManager::constructCells()
	{
		for (int i = 0; i < _xGridSize; i++)
		{
			for (int j = 0; j < _yGridSize; j++)
			{
				m_grid[i][j] = <Void>();
			}
		}

		for (int i = 0; i < _xGridSize; i++)
		{
			_grid[i][0] = std::make_shared<Void>();
			_grid[i][_yGridSize - 1] = std::make_shared<Void>();
		}

		for (int j = 0; j < _yGridSize; j++)
		{
			_grid[0][j] = std::make_shared<Void>();
			_grid[_xGridSize - 1][j] = std::make_shared<Void>();
		}


		for (int i = 0; i < _xGridSize; i++)
		{
			for (int j = 0; j < _yGridSize; j++)
			{
				_grid[i][j]->setCellIndices(i, j);
				_grid[i][j]->setCellWidth(_commonCellWidth);
			}
		}

		std::vector<std::vector<std::string>> randomGridColours =
			GridGen::randomiseGridColours(_xGridSize, _yGridSize);
		for (int i = 1; i < _xGridSize - 1; i++)
		{
			for (int j = 1; j < _yGridSize - 1; j++)
			{
				int entityId = m_cellEntities[i][j].id;
				m_cellGraphicsComponents[entityId].type = "Roon"
				m_cellGraphicsComponents[entityId].subtype = randomGridColours[i][j];
				m_cellEntities[i][j]->updatePosition();
			}
		}

	}

	LevelEntityManager::LevelEntityManager(int xNumberOfRooms, int yNumberOfRooms)
	{
		_xGridSize = std::max(xNumberOfRooms, 2) + 2;
		_yGridSize = std::max(yNumberOfRooms, 2) + 2;
		_commonCellWidth = 512.f;

		_grid.resize(_xGridSize);
		for (std::vector<std::shared_ptr<Cell>>& row : _grid)
		{
			row.resize(_yGridSize);
		}
		_loadAllTextures();
	}

	void Level::displayGrid(sf::RenderWindow& window)
	{
		for (std::vector<std::shared_ptr<Cell>>& row : _grid) {
			for (std::shared_ptr<Cell>& cell : row) {
				cell->drawSprite(window);
			};
		};
	};

	void LevelEntityManager::_loadAllTextures()
	{
		TextureDict::getInstance()->loadTexture("YellowRoom");
		TextureDict::getInstance()->loadTexture("WhiteRoom");
		TextureDict::getInstance()->loadTexture("GreenRoom");
		TextureDict::getInstance()->loadTexture("BlueRoom");
		TextureDict::getInstance()->loadTexture("RedRoom");

		TextureDict::getInstance()->loadTexture("CornerVoid");
		TextureDict::getInstance()->loadTexture("BridgeVoid");
		TextureDict::getInstance()->loadTexture("EdgeVoid");
	};

}
//std::shared_ptr<Cell> testRoom = std::make_shared<Cell>();
//std::shared_ptr<Room> testCell = std::dynamic_pointer_cast<Room>(testCell);
//testCell = std::make_shared<Room>();
//std::shared_ptr<Room> testCell3 = std::dynamic_pointer_cast<Room>(testCell);

//std::dynamic_pointer_cast<Room>(_grid[0][0])->setTrapStatus(true);

//auto checkCellCast = std::dynamic_pointer_cast<Cell>(_grid[i][j]);
//auto checkRoomCast = std::dynamic_pointer_cast<Room>(_grid[i][j]);
//if (checkCellCast || checkRoomCast)
//{
//	_grid[i][j] = std::make_shared<Room>();
//	_grid[i][j] = std::dynamic_pointer_cast<Room>(_grid[i][j]);
//}

	//std::dynamic_pointer_cast<Room>(_grid[3][3])->setTrapStatus(true);

//std::shared_ptr<Void> firstCell =
//std::dynamic_pointer_cast<Void>(_grid[0][j]);
//std::shared_ptr<Void> lastCell =
//std::dynamic_pointer_cast<Void>(_grid[_xGridSize - 1][j]);

//
//std::shared_ptr<Void> firstCell =
//std::dynamic_pointer_cast<Void>(_grid[i][0]);
//std::shared_ptr<Void> lastCell =
//std::dynamic_pointer_cast<Void>(_grid[i][_yGridSize - 1]);