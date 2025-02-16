#include "Levels/LevelEntityManager.h"

namespace Levels
{


	void LevelEntityManager::updateLevel() 
	{
		m_processLevelShift();

		srand(time(NULL));
		for (int id = 0; id < m_totalCells; id++)
		{
			if (m_cellGravityComponents[id].CellState != CellGravityComponent::STEADY)
			{
				LevelEntitySystem::adjustGravityMotion(m_cellGravityComponents[id]);
			}

			if (m_cellMoveComponents[id].cellState != CellMoveComponent::STATIC)
			{
				LevelEntitySystem::applyMovement(
					m_cellMoveComponents[id], m_cellTransformComponents[id],
					m_cellForceComponents[id], m_relativeSpeed, m_commonCellWidth
				);
			}
			if (m_cellEntities[id].components.test(CellComponentTypes::NUMBERS))
			{
				LevelEntitySystem::updateCellNumbers(m_cellNumbersComponents[id]);
			}
		}
		LevelEntitySystem::updateCollisions(m_cellTransformComponents, m_cellCollisionComponents);
		m_updateAllCellScaling();
		m_updateAllCellPositions();
	}


	vecp::Vec2f LevelEntityManager::getStartingPosition(int count)
	{
		if (count++ > 20) 
		{
			return vecp::Vec2f(m_commonCellWidth * 1.5f, m_commonCellWidth * 1.5f);
		}

		vecp::Vec2i indices = vecp::Vec2i(
			1 + rand() % (m_gridSize.x - 2),
			1 + rand() % (m_gridSize.y - 2)
			);
		
		int cellId = m_cellEntityGrid[indices.x][indices.y];
		
		vecp::Vec2f goalPosition = m_cellTransformComponents[m_goalId].position;
		vecp::Vec2f startPosition = m_cellTransformComponents[cellId].position;
		
		float goalDistance = (goalPosition - startPosition).mag();
		float halfWidth = 0.5f * (float)m_gridSize.x * m_commonCellWidth;

		if (m_cellTrapComponents[cellId].isTrapped || goalDistance < halfWidth)
		{
			startPosition = getStartingPosition(count);
		}

		return startPosition;
	}

	// A simple, humble Getter function.
	float LevelEntityManager::getCommonCellWidth()
	{
		return m_commonCellWidth;
	}

	// A simple, humble Getter function.
	vecp::Vec2i LevelEntityManager::getGridSize()
	{
		return m_gridSize;
	}


	// Render a texture of repeated bottomless voids as the lowest layer of the level.
	// This must be called before LevelEntityManager::renderLevel during each draw window.
	void LevelEntityManager::renderBackground(sf::RenderWindow& window)
	{
		window.draw(m_backgroundSprite);
		for (CellGraphicsComponent graphics : this->m_cellGraphicsComponents)
		{
			if (graphics.isBackground)
			{
				window.draw(graphics.sprite);
			}
		}
	}

	// Render all entities on top of the previously rendered background texture.
	// This must be called after LevelEntityManager::renderBackground during each draw loop.
	void LevelEntityManager::renderLevel(sf::RenderWindow& window)
	{
		for (int i = 0; i < m_totalCells; i++)
		{
			if (m_cellGraphicsComponents[i].isBackground)
			{
				continue;
			}
			window.draw(m_cellGraphicsComponents[i].sprite);
			if (m_cellNumbersComponents[i].isActive)
			{
				window.draw(m_cellNumbersComponents[i].panelBackground);
				window.draw(m_cellNumbersComponents[i].text);
			}
			if (m_cellPanelsComponents[i].isVisible)
			{
				sf::Sprite& panels = m_cellPanelsComponents[i].sprite;
				CellTransformComponent& transform = m_cellTransformComponents[i];
				panels.setPosition(transform.position.x, transform.position.y);
				LevelEntitySystem::scaleCellSprite(m_cellPanelsComponents[i].sprite, transform.cellWidth);
				window.draw(panels);
			}
		}
	};

	// Resets the forces (set to 0.f) which drive the movement of Cell entities.
	// This function should be called at the beginning of each draw loop.
	// This function must be called before LevelEntity::updateLevel().
	void LevelEntityManager::clearForces()
	{
		for (CellForceComponent& force : m_cellForceComponents)
		{
			force.netForce = vecp::Vec2f(0.f, 0.f);
		}
	}

	DetectedLevelCollisions LevelEntityManager::getCircleCollisions(
		const Actors::ActorCollisionComponent& actorCollision)
	{
		DetectedLevelCollisions detectedCollisions;
		
		const Physics::CircleParams& actorCircle = actorCollision.broadCircle.getCircle();

		int componentIndex = -1;
		for (CellCollisionComponent& cellCollision : m_cellCollisionComponents)
		{
			componentIndex++;
			if (!Physics::checkIntersection(cellCollision.broadCircle.getCircle(), actorCircle))
			{
				continue;
			}
			if (cellCollision.isBlocked == true)
			{
				cellCollision.blocker.setCellPosition(
					this->m_cellTransformComponents[componentIndex].position
				);
				cellCollision.blocker.setCellWidth(this->m_commonCellWidth);
			}
			LevelEntitySystem::getWallCollisions(detectedCollisions, cellCollision, actorCircle);
			LevelEntitySystem::getFloorCollisions(
				detectedCollisions, cellCollision, m_cellForceComponents[componentIndex], actorCircle
			);
			if (detectedCollisions.isFloorDetected == false)
			{
				detectedCollisions.voidCentre =
					((actorCircle.position / m_commonCellWidth).floor() + 0.5f) * m_commonCellWidth;
			}
		}

		return detectedCollisions;

	}


	LevelEntityManager::LevelEntityManager(LevelSettings settings)
	{
		m_gridSize = vecp::Vec2i(
			std::max(settings.size.x, 2) + 2,
			std::max(settings.size.y, 2) + 2
		);
		m_commonCellWidth = settings.cellWidth;

		m_totalCells = m_gridSize.x * m_gridSize.y;


		// Update the vector sizes for all entities and components.
		m_cellEntityGrid.resize(m_gridSize.x);
		for (std::vector<int>& row : m_cellEntityGrid)
		{
			row.resize(m_gridSize.y);
		}

		m_cellEntities.resize(m_totalCells);
		m_cellTransformComponents.resize(m_totalCells);
		m_cellGraphicsComponents.resize(m_totalCells);
		m_cellCollisionComponents.resize(m_totalCells);
		m_cellForceComponents.resize(m_totalCells);
		m_cellTypeComponents.resize(m_totalCells);
		m_cellMoveComponents.resize(m_totalCells);
		m_cellGravityComponents.resize(m_totalCells);
		m_cellNumbersComponents.resize(m_totalCells);
		m_cellPanelsComponents.resize(m_totalCells);
		m_cellTrapComponents.resize(m_totalCells);

		// The maze start off static, so initailly no overlaying panels will be displayed.
		for (CellGraphicsComponent panels : m_cellPanelsComponents)
		{
			panels.isVisible = false;
		}

		// Assign an id to each entity which corresponds to its universal position in
		// the component vectors.
		int counter = 0;
		for (int i = 0; i < m_gridSize.x; i++)
		{
			for (int j = 0; j < m_gridSize.y; j++)
			{
				m_cellEntityGrid[i][j] = counter;
				m_cellEntities[counter].cellId = counter;
				m_cellTransformComponents[counter].cellIndices = vecp::Vec2i(i, j);
				counter += 1;
			}
		}

		// Assign the type of each cell entity depending on its location in the grid.
		// Mark the active components of each cell entity, as determined by its type.
		// In the case of rooms, also assign its colour. 
		LevelFactory::assignCellTypes(m_cellEntityGrid, m_cellTypeComponents);
		m_goalId = LevelFactory::selectGoalLocation(m_cellEntityGrid, m_cellTypeComponents);
		LevelFactory::setActiveComponentTypes(m_cellTypeComponents, m_cellEntities);
		
		// For each cell entity of type 'Room', assign it set of three, three-digit numbers.
		this->m_buildCellNumbers();

		// Assign the main sprite to each cell depending on its type.
		// Also construct the underlying background texture. 
		LevelFactory::loadAllLevelTextures();
		LevelFactory::createBackground(m_backgroundSprite, m_gridSize.x, m_gridSize.y);
		LevelFactory::addTextures(m_cellTypeComponents, m_cellGraphicsComponents);

		sf::Texture& texture = Assets::TextureDict::getInstance()->getTexture("PanelsGoal");
		m_cellPanelsComponents[m_goalId].sprite.setTexture(texture);
		m_cellPanelsComponents[m_goalId].isVisible = true;


		// Create and configure the collision components of each cell entity, as determined by 
		// its type.
		LevelFactory::addCollisions(m_cellTypeComponents, m_cellCollisionComponents);
		LevelEntitySystem::updateCollisions(m_cellTransformComponents, m_cellCollisionComponents);
	
		// Finally, scale all revelant component properties.
		this->m_scaleFixedWidthComponents();
	}


	void LevelEntityManager::m_buildCellNumbers()
	{
		LevelFactory::selectTrappedRooms(m_cellEntities, m_cellTrapComponents);
		for (int i = 0; i < m_totalCells; i++) 
		{
			if (m_cellEntities[i].components.test(CellComponentTypes::NUMBERS))
			{
				LevelFactory::addNumbers(m_cellTransformComponents[i], 
					m_cellNumbersComponents[i]);
			}
		}
		LevelFactory::assignNumbers(m_cellEntities, m_cellTrapComponents, m_cellNumbersComponents);
	}

	void LevelEntityManager::m_updateAllCellScaling()
	{

		for (int i = 0; i < m_totalCells; i++)
		{
			CellTransformComponent& transform = m_cellTransformComponents[i];
			CellGravityComponent& gravity = m_cellGravityComponents[i];
			float cellWidth = transform.cellWidth * gravity.currentScale;

			if (gravity.CellState == CellGravityComponent::STEADY)
			{
				cellWidth = transform.cellWidth;
			};

			sf::Sprite& sprite = m_cellGraphicsComponents[i].sprite;
			if (sprite.getLocalBounds().width != cellWidth)
			{
				LevelEntitySystem::scaleCellSprite(sprite, cellWidth);
			}
		}

	}


	void LevelEntityManager::m_updateAllCellPositions()
	{
		for (int i = 0; i < m_totalCells; i++)
		{
			float x = m_cellTransformComponents[i].position.x;
			float y = m_cellTransformComponents[i].position.y;

			m_cellGraphicsComponents[i].sprite.setPosition(x, y);
			m_cellPanelsComponents[i].sprite.setPosition(x, y);

			CellNumbersComponent& numbers = m_cellNumbersComponents[i];
			//LevelEntitySystem::updateCellNumbers(numbers);

			sf::Vector2f position{
				x + m_commonCellWidth * numbers.relativePosition.x,
				y + m_commonCellWidth * numbers.relativePosition.y
			};
			numbers.text.setPosition(position);
			numbers.panelBackground.setPosition(position);
		}
	}

	void LevelEntityManager::m_processLevelShift()
	{
		if (m_currentMoveActions.size() == 0)
		{
			m_currentShiftAxis = (m_currentShiftAxis == LevelEntityManager::ROW)
				? LevelEntityManager::COLUMN : LevelEntityManager::ROW;
			for (int i = 0; i < 3; i++)
			{
				LevelEntitySystem::createMoveAction(m_currentShiftAxis, m_cellEntityGrid,
					m_cellMoveComponents, m_currentMoveActions);
				LevelEntitySystem::updateCellIndicies(m_cellEntityGrid, m_cellTransformComponents,
					m_cellMoveComponents, 0, m_cellEntityGrid.size() - 1);
			}

		}

		for (LevelMoveAction& action : m_currentMoveActions)
		{

			switch (action.getCurrentActionState())
			{
			case LevelMoveAction::STARTING:
				if (action.hasCountdownCompleted(
					LevelEntitySystem::getDeltaTime(), m_cellPanelsComponents)
					)
				{
					m_cellNumbersComponents[action.getDropCellId()].isActive = false;
					action.beginDrop(m_cellGravityComponents, m_cellCollisionComponents);
				}
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
					transform.position = vecp::Vec2f(
						(transform.cellIndices.x + 0.5f) * m_commonCellWidth,
						(transform.cellIndices.y + 0.5f) * m_commonCellWidth
					);
					m_cellCollisionComponents[action.getDropCellId()].isBlocked = true;
					action.beginRise(m_cellGravityComponents);
				}
				break;
			case LevelMoveAction::CLIMBING:
				if (action.hasRiseCompleted(m_cellGravityComponents))
				{
					m_cellNumbersComponents[action.getDropCellId()].isActive = true;
					m_cellCollisionComponents[action.getDropCellId()].isBlocked = false;
					action.endAction(m_cellCollisionComponents);
				}
				break;
			case LevelMoveAction::ENDED:
				break;
			default:
				break;
			};


			switch (action.getCurrentActionState())
			{
			case LevelMoveAction::DROPPING:
			case LevelMoveAction::CLIMBING:
				m_cellGraphicsComponents[action.getDropCellId()].isBackground = true;
				break;
			default:
				m_cellGraphicsComponents[action.getDropCellId()].isBackground = false;
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
	}

	void LevelEntityManager::m_scaleFixedWidthComponents()
	{
		m_backgroundSprite.setScale(
			m_commonCellWidth * m_gridSize.x / m_backgroundSprite.getLocalBounds().width,
			m_commonCellWidth * m_gridSize.y / m_backgroundSprite.getLocalBounds().height
		);

		for (int id = 0; id < this->m_totalCells; id++)
		{
			// Scale the single square panels for the number text display.
			CellEntity& entity = this->m_cellEntities[id];
			if (entity.components.test(CellComponentTypes::NUMBERS))
			{
				float panelWidth = 0.22f * m_commonCellWidth;
				sf::RectangleShape& panel = m_cellNumbersComponents[id].panelBackground;
				panel.setSize(sf::Vector2f(panelWidth, panelWidth));
				panel.setOrigin(0.5f * panelWidth, 0.5f * panelWidth);
			}

			// Scale the main sprite of each cell.
			if (!entity.components.test(CellComponentTypes::MOVE))
			{
				LevelEntitySystem::scaleCellSprite(m_cellGraphicsComponents[id].sprite, m_commonCellWidth);
			
				if (m_cellGraphicsComponents[id].isReversed)
				{
					sf::Sprite& sprite = m_cellGraphicsComponents[id].sprite;
					float cellWidth = m_commonCellWidth;
					sprite.setOrigin(
						sprite.getLocalBounds().width * 0.5f,
						sprite.getLocalBounds().height * 0.5f
					);
					sprite.setScale(
						-1.f * cellWidth / sprite.getLocalBounds().width,
						cellWidth / sprite.getLocalBounds().height
					);
					sprite.setOrigin(
						sprite.getLocalBounds().width * 0.5f,
						sprite.getLocalBounds().height * 0.5f
					);
	
				}
			}

			// Set all cell positions in their respective transform components.
			for (CellTransformComponent& transform : m_cellTransformComponents)
			{
				transform.cellWidth = m_commonCellWidth;
				transform.position = vecp::Vec2f(
					(transform.cellIndices.x + 0.5f) * transform.cellWidth,
					(transform.cellIndices.y + 0.5f) * transform.cellWidth
				);
			}

			// Scale all walls and floors of each cell.
			if (entity.components.test(CellComponentTypes::COLLISION))
			{
				CellCollisionComponent& collision = m_cellCollisionComponents[id];
				CellTransformComponent& transform = m_cellTransformComponents[id];
				
				collision.broadCircle.setRadius(collision.relativeBroadRadius * m_commonCellWidth);
				for (CellStaticRectangle& wall : collision.staticWalls)
				{
					wall.setCellWidth(transform.cellWidth);
				}
				for (CellStaticRectangle& sensor : collision.sensors)
				{
					sensor.setCellWidth(transform.cellWidth);
				}
				for (CellStaticRectangle& floor : collision.staticFloors)
				{
					floor.setCellPosition(transform.position);
					floor.setCellWidth(transform.cellWidth);
				}
			}

		}
	}

}


// This setter function not only sets the value of the cell (room) dimensions
// but it automaticallyre scales all Transform and Collision Components.
//void LevelEntityManager::setCommonCellWidth(float commonCellWidth)
//{
//	m_commonCellWidth = commonCellWidth;
//	for (CellTransformComponent& transform : m_cellTransformComponents)
//	{
//		transform.cellWidth = commonCellWidth;
//		transform.position = vecp::Vec2f(
//			(transform.cellIndices.x + 0.5f) * transform.cellWidth,
//			(transform.cellIndices.y + 0.5f) * transform.cellWidth
//		);
//	}
//	LevelFactory::updateCollisions(m_cellTransformComponents, m_cellCollisionComponents);
//
//	this->m_scaleFixedWidthComponents();
//}


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