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
		LevelFactory::updateCollisions(m_cellTransformComponents, m_cellCollisionComponents);
	}

	float LevelEntityManager::getCommonCellWidth()
	{
		return m_commonCellWidth;
	}

	Physics::Vec2i LevelEntityManager::getGridSize()
	{
		return Physics::Vec2i(m_xGridSize, m_yGridSize);
	}

	void LevelEntityManager::updateAllCellScaling()
	{
		m_backgroundSprite.setScale(
			m_commonCellWidth * m_xGridSize / m_backgroundSprite.getLocalBounds().width,
			m_commonCellWidth * m_yGridSize / m_backgroundSprite.getLocalBounds().height
		);

		for (int i = 0; i < m_totalCells; i++)
		{
			CellTransformComponent& transform = m_cellTransformComponents[i];
			CellGravityComponent& gravity = m_cellGravityComponents[i];
			sf::Sprite& sprite = m_cellGraphicsComponents[i].sprite;
			
			float cellWidth = transform.cellWidth * gravity.currentScale;
			if (gravity.CellState == CellGravityComponent::STEADY)
			{
				cellWidth = transform.cellWidth;

			};
			
			if (sprite.getLocalBounds().width != cellWidth)
			{
				sprite.setScale(
					cellWidth / sprite.getLocalBounds().width,
					cellWidth / sprite.getLocalBounds().height
				);
				sprite.setOrigin(
					sprite.getLocalBounds().width * 0.5f,
					sprite.getLocalBounds().height * 0.5f
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

	void LevelEntityManager::processLevelShift()
	{
		if (m_currentMoveActions.size() == 0)
		{
			m_currentShiftAxis = (m_currentShiftAxis == LevelEntityManager::ROW) 
				? LevelEntityManager::COLUMN : LevelEntityManager::ROW;
			LevelEntitySystem::createMoveAction(m_currentShiftAxis, m_cellEntityGrid,
				m_cellMoveComponents, m_currentMoveActions);
			LevelEntitySystem::updateCellIndicies(m_cellEntityGrid, m_cellTransformComponents,
				m_cellMoveComponents, 0, m_cellEntityGrid.size() - 1);
		}
 
		for (LevelMoveAction& action : m_currentMoveActions)
		{
			switch (action.getCurrentActionState())
			{
			case LevelMoveAction::STARTING:
				action.beginDrop(m_cellGravityComponents, m_cellCollisionComponents);
				break;
			case LevelMoveAction::DROPPING:
				if (action.hasDropCompleted(m_cellGravityComponents))
				{
					action.beginShift(m_cellMoveComponents);
				}
				break;
			case LevelMoveAction::SHIFTING:
				if (action.hasShiftCompleted(m_cellMoveComponents))
				{
					CellTransformComponent& transform = 
						m_cellTransformComponents[action.getDropCellId()];
					transform.position = Physics::Vec2f(
						(transform.cellIndices.x + 0.5f) * m_commonCellWidth,
						(transform.cellIndices.y + 0.5f) * m_commonCellWidth
					);
					action.beginRise(m_cellGravityComponents);
				}
				break;
			case LevelMoveAction::CLIMBING:
				if (action.hasRiseCompleted(m_cellGravityComponents))
				{
					action.endAction(m_cellCollisionComponents);
				}
				break;
			case LevelMoveAction::ENDED:
				break;
			default:
				break;
			};
		}

		// Remove actions which have completed (ended)
		for (std::vector<LevelMoveAction>::iterator iter 
			= m_currentMoveActions.begin(); iter != m_currentMoveActions.end();)
		{
			if (iter->getCurrentActionState() == LevelMoveAction::ENDED)
			{
				iter = m_currentMoveActions.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (int i = 0; i < m_totalCells; i++)
		{
			if (m_cellGravityComponents[i].CellState != CellGravityComponent::STEADY)
			{
				LevelEntitySystem::adjustGravityMotion(m_cellGravityComponents[i]);
			}
				
			if (m_cellMoveComponents[i].cellState != CellMoveComponent::STATIC)
			{
				LevelEntitySystem::applyMovement(
					m_cellMoveComponents[i], m_cellTransformComponents[i],
					m_cellForceComponents[i], m_relativeSpeed, m_commonCellWidth
				);
			}
		}
		LevelFactory::updateCollisions(m_cellTransformComponents, m_cellCollisionComponents);
	}

	void LevelEntityManager::renderBackground(sf::RenderWindow& window)
	{
		window.draw(m_backgroundSprite);
	}

	void LevelEntityManager::renderLevel(sf::RenderWindow& window)
	{
		for (int i = 0; i < m_totalCells; i++)
		{
			window.draw(m_cellGraphicsComponents[i].sprite);
		}
	};

	void LevelEntityManager::clearForces()
	{
		for (CellForceComponent& force : m_cellForceComponents)
		{
			force.netForce = Physics::Vec2f(0.f, 0.f);
		}
	}

	DetectedLevelCollisions LevelEntityManager::getCircleCollisions(
		const Actors::ActorCollisionComponent& actorCollision)
	{
		DetectedLevelCollisions detectedCollisions;
		const Physics::CircleParams& actorCircle = actorCollision.broadCircle.getCircle();
		int componentIndex = -1;
		for (const CellCollisionComponent& cellCollision : m_cellCollisionComponents)
		{
			componentIndex++;
			if (!Physics::checkIntersection(cellCollision.broadCircle.getCircle(), actorCircle))
			{
				continue;
			}
			LevelEntitySystem::getWallCollisions(detectedCollisions, cellCollision, actorCircle);
			LevelEntitySystem::getFloorCollisions(
				detectedCollisions, cellCollision, m_cellForceComponents[componentIndex], actorCircle
			);
			if (detectedCollisions.isFloorDetected == false)
			{
				detectedCollisions.voidCentre = 
					(actorCircle.position / m_commonCellWidth).floor() + 0.5f;
			}
		}

		return detectedCollisions;

	}

	LevelEntityManager::LevelEntityManager(int xNumberOfRooms, int yNumberOfRooms)
	{
		m_xGridSize = std::max(xNumberOfRooms, 2) + 2;
		m_yGridSize = std::max(yNumberOfRooms, 2) + 2;
		m_commonCellWidth = 512.f;

		m_totalCells = m_xGridSize * m_yGridSize;

		m_cellEntityGrid.resize(m_xGridSize);
		for (std::vector<int>& row : m_cellEntityGrid)
		{
			row.resize(m_yGridSize);
		}

		m_cellEntities.resize(m_totalCells);
		m_cellTransformComponents.resize(m_totalCells);
		m_cellGraphicsComponents.resize(m_totalCells);
		m_cellCollisionComponents.resize(m_totalCells);
		m_cellForceComponents.resize(m_totalCells);
		m_cellTypeComponents.resize(m_totalCells);
		m_cellMoveComponents.resize(m_totalCells);
		m_cellGravityComponents.resize(m_totalCells);

		int counter = 0;
		for (int i = 0; i < m_xGridSize; i++)
		{
			for (int j = 0; j < m_yGridSize; j++)
			{
				m_cellEntityGrid[i][j] = counter;
				m_cellTransformComponents[counter].cellIndices = Physics::Vec2i(i, j);
				counter += 1;
			}
		}

		LevelFactory::loadAllLevelTextures();
		LevelFactory::createBackground(m_backgroundSprite, m_xGridSize, m_yGridSize);
		LevelFactory::assignCellTypes(m_cellEntityGrid, m_cellTypeComponents);
		LevelFactory::addTextures(m_cellTypeComponents, m_cellGraphicsComponents);
		LevelFactory::addCollisions(m_cellTypeComponents, m_cellCollisionComponents);
		LevelFactory::updateCollisions(m_cellTransformComponents, m_cellCollisionComponents);
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