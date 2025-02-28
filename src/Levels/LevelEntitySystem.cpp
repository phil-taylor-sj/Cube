#include "Levels/LevelEntitySystem.h"

namespace Levels
{
	void LevelEntitySystem::setDeltaTime(float deltaTime)
	{
		m_deltaTime = deltaTime;
	}

	float LevelEntitySystem::getDeltaTime()
	{
		return m_deltaTime;
	}

	void LevelEntitySystem::getWallCollisions(
		DetectedLevelCollisions& detectedCollisions, 
		const CellCollisionComponent& cellCollision,
		const Physics::CircleParams& actorCircle
	)
	{
		if (cellCollision.isBlocked == true)
		{
			if (Physics::checkIntersection(cellCollision.blocker.getRectangle(), actorCircle))
			{
				detectedCollisions.blockers.push_back(cellCollision.blocker.getRectangle());
			}
		}

		if (cellCollision.areCollisionsActive == false)
		{
			return;
		}

		for (const CellStaticRectangle& wallCollision : cellCollision.staticWalls)
		{
			if (Physics::checkIntersection(wallCollision.getRectangle(), actorCircle))
			{
				detectedCollisions.staticWalls.push_back(wallCollision.getRectangle());
			}
		}

		
		if (cellCollision.isBlocked == true)
		{
			if(Physics::checkIntersection(cellCollision.blocker.getRectangle(), actorCircle))
			{
				detectedCollisions.staticWalls.push_back(cellCollision.blocker.getRectangle());
			}
		}
	}

	void LevelEntitySystem::getFloorCollisions(
		DetectedLevelCollisions& detectedCollisions, 
		const CellCollisionComponent& cellCollision,
		const CellForceComponent& cellForce,
		const Physics::CircleParams& actorCircle
	)
	{
		if (cellCollision.isFloorActive == false)
		{
			return;
		}
			
		for (const CellStaticRectangle& floorCollision : cellCollision.staticFloors)
		{
			// Create a new circle for checking actor contact with the floor
			float baseScaleFactor = 0.2f;
			Physics::CircleParams baseCircle = actorCircle;
			baseCircle.radius = actorCircle.radius * baseScaleFactor;
			baseCircle.radiusSquared = pow(baseCircle.radius, 2); 

			if (Physics::checkIntersection(
				floorCollision.getRectangle(), baseCircle)
				)
			{
				// Move the actor with the floor if in contact
				detectedCollisions.isFloorDetected = true;
				if (cellForce.isMoving)
				{
					detectedCollisions.floorForce += cellForce.netForce;
				}
			}
		}
	}

	void LevelEntitySystem::createMoveAction(
		int axis,
		std::vector<std::vector<int>>& cellGrid,
		std::vector<CellMoveComponent>& moveComponents,
		std::vector<LevelMoveAction>& moveActions
	)
	{
		srand(time(NULL));
		enum
		{
			COLUMN = 0,
			ROW = 1
		};

		int firstColumnIndex = 1;
		int lastColumnIndex = cellGrid.size() - 2;
		int firstRowIndex = 1;
		int lastRowIndex = cellGrid[0].size() - 2;

		int columnIndex = 0;
		int rowIndex = 0;
		int primaryIndex = 0;

		// Check that the row/column index is not held by any existing action
		bool idExists = true;
		while(idExists == true)
		{
			columnIndex = firstColumnIndex + rand() % (lastColumnIndex);
			rowIndex = firstRowIndex + rand() % (lastRowIndex);
			primaryIndex = (axis == COLUMN) ? columnIndex : rowIndex;
			idExists = false;
			if (moveActions.size() > 0)
			{
				for (const LevelMoveAction& action : moveActions)
				{
					if (primaryIndex == action.getRowOrColumn())
					{
						idExists = true;
					}
				}
			}
		}
		// Randomly selcted move direction along corresponding axis
		CellMoveComponent::State direction = (axis == COLUMN) 
			? (rand() % (2) == 0)
				? CellMoveComponent::MOVING_UP 
				: CellMoveComponent::MOVING_DOWN
			: (rand() % (2) == 0)
				? CellMoveComponent::MOVING_LEFT
				: CellMoveComponent::MOVING_RIGHT;
	

		// Create new action
		LevelMoveAction newAction = LevelMoveAction(primaryIndex);
		newAction.setDropCellId(cellGrid[columnIndex][rowIndex]);
		if (axis == COLUMN)
		{
			newAction.setShiftAction(
				(rowIndex == firstRowIndex)
					? CellMoveComponent::MOVING_UP 
				    : (rowIndex == lastRowIndex)
						? CellMoveComponent::MOVING_DOWN 
				        : direction);
		}
		if (axis == ROW)
		{
			newAction.setShiftAction(
				(columnIndex == firstColumnIndex)
					? CellMoveComponent::MOVING_LEFT
					: (columnIndex == lastColumnIndex)
						? CellMoveComponent::MOVING_RIGHT
						: direction);
		}

		// add cells to shift
		switch (newAction.getShiftAction())
		{
		case CellMoveComponent::MOVING_UP:
			for (int i = rowIndex + 1; i <= lastRowIndex; i++)
			{
				newAction.addShiftCellId(cellGrid[columnIndex][i]);
				std::swap(cellGrid[columnIndex][i-1],
					cellGrid[columnIndex][i]);
			}
			break;
		case CellMoveComponent::MOVING_DOWN:

			for (int i = rowIndex - 1; i >= firstRowIndex; i--)
			{	
				newAction.addShiftCellId(cellGrid[columnIndex][i]);
				std::swap(cellGrid[columnIndex][i + 1],
					cellGrid[columnIndex][i]);
			}
			break;
		case CellMoveComponent::MOVING_LEFT:
			for (int i = columnIndex + 1; i <= lastColumnIndex; i++)
			{
				newAction.addShiftCellId(cellGrid[i][rowIndex]);
				std::swap(cellGrid[i - 1][rowIndex],
					cellGrid[i][rowIndex]);
			}
			break;
		case CellMoveComponent::MOVING_RIGHT:
			for (int i = columnIndex - 1; i >= firstColumnIndex; i--)
			{
				newAction.addShiftCellId(cellGrid[i][rowIndex]);
				std::swap(cellGrid[i + 1][rowIndex],
					cellGrid[i][rowIndex]);
			}
			break;
		default:
			break;
		}
		moveActions.push_back(newAction);
	}

	void LevelEntitySystem::updateCellIndicies(
		const std::vector<std::vector<int>>& cellGrid,
		std::vector<CellTransformComponent>& transformComponents,
		std::vector<CellMoveComponent>& moveComponents,
		int startIndex, int endIndex
	)
	{
		for (int i = startIndex; i <= endIndex; i++)
		{
			for (int j = 0; j < cellGrid[i].size(); j++)
			{
				int entityId = cellGrid[i][j];
				vecp::Vec2i currentIndicies = vecp::Vec2i(i,j);
				transformComponents[entityId].cellIndices = currentIndicies;
				moveComponents[entityId].destinationIndicies = currentIndicies;
			}
		}
	}

	void LevelEntitySystem::adjustGravityMotion(CellGravityComponent& gravity)
	{
		if (gravity.CellState == CellGravityComponent::STEADY)
		{
			return;
		}
		gravity.timer += m_deltaTime;
		//float time = gravity.timer.getElapsedTime().asSeconds();
		float timeFraction = std::min(gravity.timer/gravity.verticalTime, 1.f);

		switch (gravity.CellState)
		{
		case CellGravityComponent::FALLING:
			gravity.currentScale = 1.f - pow(timeFraction, 2);
			if (timeFraction == 1.f)
			{
				gravity.CellState = CellGravityComponent::VANISHED;
			}
			break;
		case CellGravityComponent::RISING:
			gravity.currentScale = pow(timeFraction, 2);
			if (timeFraction == 1.f)
			{
				gravity.currentScale = 1.f;
				gravity.CellState = CellGravityComponent::STEADY;
			}
			break;
		case CellGravityComponent::VANISHED:
			gravity.currentScale = 0.f;
			break;
		default:
			break;
		};
	}
	
	void LevelEntitySystem::applyMovement(
		CellMoveComponent& move,
		CellTransformComponent& transform,
		CellForceComponent& force,
		float relativeSpeed,
		float commonCellWidth
	)
	{
		vecp::Vec2f destination = vecp::Vec2f(
			(move.destinationIndicies.x + 0.5f) * commonCellWidth,
			(move.destinationIndicies.y + 0.5f) * commonCellWidth
		);
		float distance = relativeSpeed * commonCellWidth;
		switch (move.cellState)
		{
		case CellMoveComponent::MOVING_UP:
			transform.position.y -= distance;
			force.netForce.y -= distance;
			if (transform.position.y <= destination.y)
			{
				transform.position.y = destination.y;
				move.cellState = CellMoveComponent::STATIC;
			}
			break;
		case CellMoveComponent::MOVING_DOWN:
			transform.position.y += distance;
			force.netForce.y = distance;
			if (transform.position.y >= destination.y)
			{
				transform.position.y = destination.y;
				move.cellState = CellMoveComponent::STATIC;
			}
			break;
		case CellMoveComponent::MOVING_LEFT:
			transform.position.x -= distance;
			force.netForce.x -= distance;
			if (transform.position.x <= destination.x)
			{
				transform.position.x = destination.x;
				move.cellState = CellMoveComponent::STATIC;
			}
			break;
		case CellMoveComponent::MOVING_RIGHT:
			transform.position.x += distance;
			force.netForce.x += distance;
			if (transform.position.x >= destination.x)
			{
				transform.position.x = destination.x;
				move.cellState = CellMoveComponent::STATIC;
			}
			break;
		default:
			break;
		}
	}

	void LevelEntitySystem::scaleCellSprite(sf::Sprite& sprite, float cellWidth)
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

	void LevelEntitySystem::updateCellNumbers(
		CellNumbersComponent& numbers
	)
	{
		numbers.timer += m_deltaTime;
		if (numbers.timer < numbers.period)
		{
			return;
		}
	
		numbers.timer = 0.f;  // TODO: Update to get remainder
		//numbers.period = 1.5f + 2.f * ((rand() % 9) * 0.1f);
		CellPanel current = numbers.currentPanel;
		//while (numbers.currentPanel == current)
		//{
			numbers.currentPanel = m_panels[rand() % 9];
		//}
		numbers.currentPanel = m_panels[4];
		numbers.relativePosition = m_panelPositions[numbers.currentPanel];
		numbers.currentIndex = (numbers.currentIndex < numbers.numbers.size() - 1)
			? numbers.currentIndex + 1 
			: 0;
		numbers.text.setString(numbers.numbers[numbers.currentIndex]);
		sf::FloatRect shape = numbers.text.getLocalBounds();
		numbers.text.setOrigin(0.5 * shape.width, 0.5f * shape.height);

	}

	void LevelEntitySystem::updateCollisions(
		const std::vector<CellTransformComponent>& cellTransforms,
		std::vector<CellCollisionComponent>& cellCollisions)
	{
		for (int i = 0; i < cellCollisions.size(); i++)
		{
			cellCollisions[i].broadCircle.setPosition(cellTransforms[i].position);
			for (CellStaticRectangle& wall : cellCollisions[i].staticWalls)
			{
				wall.setCellPosition(cellTransforms[i].position);
			}
			for (CellStaticRectangle& floor : cellCollisions[i].staticFloors)
			{
				floor.setCellPosition(cellTransforms[i].position);
			}
		}
	}


	float LevelEntitySystem::m_deltaTime = 0.f;

	float LevelEntitySystem::m_offset = 0.265625;

	std::map<int, CellPanel> LevelEntitySystem::m_panels = {
		{0, CellPanel::TOP_LEFT},
		{1, CellPanel::TOP_MID},
		{2, CellPanel::TOP_RIGHT},
		{3, CellPanel::MID_LEFT},
		{4, CellPanel::MID_MID},
		{5, CellPanel::MID_RIGHT},
		{6, CellPanel::BOT_LEFT},
		{7, CellPanel::BOT_MID},
		{8, CellPanel::BOT_RIGHT}
	};

	std::map<CellPanel, vecp::Vec2f> LevelEntitySystem::m_panelPositions = {
		{CellPanel::TOP_LEFT,  vecp::Vec2f(-1.f * m_offset, -1.f * m_offset)},
		{CellPanel::TOP_MID,   vecp::Vec2f(0.f * m_offset, -1.f * m_offset)},
		{CellPanel::TOP_RIGHT, vecp::Vec2f(1.f * m_offset, -1.f * m_offset)},
		{CellPanel::MID_LEFT,  vecp::Vec2f(-1.f * m_offset,  0.f * m_offset)},
		{CellPanel::MID_MID,   vecp::Vec2f(0.f * m_offset,  0.f * m_offset)},
		{CellPanel::MID_RIGHT, vecp::Vec2f(1.f * m_offset,  0.f * m_offset)},
		{CellPanel::BOT_LEFT,  vecp::Vec2f(-1.f * m_offset,  1.f * m_offset)},
		{CellPanel::BOT_MID,   vecp::Vec2f(0.f * m_offset,  1.f * m_offset)},
		{CellPanel::BOT_RIGHT, vecp::Vec2f(1.f * m_offset,  1.f * m_offset)}
	};
}