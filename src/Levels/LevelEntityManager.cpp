#include "Levels/LevelEntityManager.h"

namespace Levels
{
	void LevelEntityManager::setCommonCellWidth(float commonCellWidth)
	{
		m_commonCellWidth = commonCellWidth;

		for (CellTransformComponent& transform : m_cellTransformComponents)
		{
			transform.cellWidth = commonCellWidth;
			transform.position = Physics::Vec2f(
				(transform.cellIndices.x + 0.5f) * transform.cellWidth,
				(transform.cellIndices.y + 0.5f) * transform.cellWidth
			);
		}
	}

	void LevelEntityManager::updateAllCellScaling()
	{
		for (int i = 0; i < m_totalCells; i++)
		{
			CellTransformComponent& transform = m_cellTransformComponents[i];
			sf::Sprite& sprite = m_cellGraphicsComponents[i].sprite;
			
			if (sprite.getLocalBounds().width != transform.cellWidth)
			{
				sprite.scale(
					transform.cellWidth / sprite.getLocalBounds().width,
					transform.cellWidth / sprite.getLocalBounds().height
				);
			}
		}

		updateAllCellPositions();
	}

	void LevelEntityManager::updateAllCellPositions()
	{
		for (int i = 0; i < m_totalCells; i++)
		{
			CellTransformComponent& transform = m_cellTransformComponents[i];
			sf::Sprite& sprite = m_cellGraphicsComponents[i].sprite;

			sprite.setPosition(transform.position.x, transform.position.y);
		}
	}

	void LevelEntityManager::renderLevel(sf::RenderWindow& window)
	{
		for (int i = 0; i < m_totalCells; i++)
		{
			window.draw(m_cellGraphicsComponents[i].sprite);
		}
	};

	LevelEntityManager::LevelEntityManager(int xNumberOfRooms, int yNumberOfRooms)
	{
		m_xGridSize = std::max(xNumberOfRooms, 2) + 2;
		m_yGridSize = std::max(yNumberOfRooms, 2) + 2;
		m_commonCellWidth = 512.f;

		m_totalCells = m_xGridSize * m_yGridSize;

		m_cellEntities.resize(m_xGridSize);
		for (std::vector<CellEntity>& row : m_cellEntities)
		{
			row.resize(m_yGridSize);
		}

		m_cellTransformComponents.resize(m_totalCells);
		m_cellGraphicsComponents.resize(m_totalCells);
		m_cellCollisionComponents.resize(m_totalCells);
		m_cellTypeComponents.resize(m_totalCells);

		int counter = 0;
		for (int i = 0; i < m_xGridSize; i++)
		{
			for (int j = 0; j < m_yGridSize; j++)
			{
				m_cellEntities[i][j].cellId = counter;
				m_cellTransformComponents[counter].cellIndices = Physics::Vec2i(i, j);
				counter += 1;
			}
		}

		LevelFactory::loadAllLevelTextures();
		LevelFactory::assignCellTypes(m_cellEntities, m_cellTypeComponents);
		LevelFactory::addTextures(m_cellTypeComponents, m_cellGraphicsComponents);
		LevelFactory::addCollision(m_cellTypeComponents, m_cellCollisionComponents);		
	}

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