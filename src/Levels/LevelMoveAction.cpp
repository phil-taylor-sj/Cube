#include "Levels/LevelMoveAction.h"

namespace Levels
{

	bool LevelMoveAction::hasCountdownCompleted(
		float deltaTime, std::vector<CellGraphicsComponent>& panelsComponents)
	{
		this->m_dropTimer += deltaTime;
		CellGraphicsComponent& panels = panelsComponents[this->m_cellToDrop];
		int stage = floor(5.f * m_dropTimer / m_dropDelay);
		panels.isVisible = true;
		Assets::TextureDict* textures = Assets::TextureDict::getInstance();
		switch (stage)
		{
		case 0:
			panels.sprite.setTexture(textures->getTexture("PanelsBlank"));
			break;
		case 1:
			panels.sprite.setTexture(textures->getTexture("PanelsDiamondOne"));
			break;
		case 2:
			panels.sprite.setTexture(textures->getTexture("PanelsDiamondTwo"));
			break;
		case 3:
			panels.sprite.setTexture(textures->getTexture("PanelsDiamondThree"));
			break;
		case 4:
			panels.sprite.setTexture(textures->getTexture("PanelsDiamondFour"));
			break;
		default:
			panels.isVisible = false;
			break;
		}
		return !panels.isVisible;
	}

	bool LevelMoveAction::hasDropCompleted(
		const std::vector<CellGravityComponent>& gravityComponents) const
	{
		if (m_actionState < DROPPING)
		{
			return false;
		}
		return gravityComponents[m_cellToDrop].CellState ==
			CellGravityComponent::VANISHED;
	}

	bool LevelMoveAction::hasShiftCompleted(
		const std::vector<CellMoveComponent>& moveComponents) const
	{
		if (m_actionState < SHIFTING)
		{
			return false;
		}
		for (int cellId : m_cellsToShift)
		{
			if (moveComponents[cellId].cellState !=
				CellMoveComponent::STATIC)
			{
				return false;
			}
		}
		return true;
	}
	
	bool LevelMoveAction::hasRiseCompleted(
		const std::vector<CellGravityComponent>& gravityComponents) const
	{
		if (m_actionState < CLIMBING)
		{
			return false;
		}
		return gravityComponents[m_cellToDrop].CellState ==
			CellGravityComponent::STEADY;
	}

	int LevelMoveAction::getRowOrColumn() const
	{
		return m_rowOrColumn;
	}

	void LevelMoveAction::beginDrop(
		std::vector<CellGravityComponent>& gravityComponents,
		std::vector<CellCollisionComponent>& collisionComponents)
	{
		m_actionState = DROPPING;
		gravityComponents[m_cellToDrop].CellState = 
			CellGravityComponent::FALLING;
		gravityComponents[m_cellToDrop].timer = 0.f;
		collisionComponents[m_cellToDrop].areCollisionsActive = false;
		collisionComponents[m_cellToDrop].isFloorActive = false;
	}

	void LevelMoveAction::beginShift(
		std::vector<CellMoveComponent>& moveComponents)
	{	
		m_actionState = SHIFTING;
		for (int cellIndex : m_cellsToShift)
		{
			moveComponents[cellIndex].cellState = m_shiftAction;
		}
	}

	void LevelMoveAction::beginRise(
		std::vector<CellGravityComponent>& gravityComponents
		)
	{
		m_actionState = CLIMBING;
		gravityComponents[m_cellToDrop].CellState =
			CellGravityComponent::RISING;
		gravityComponents[m_cellToDrop].timer = 0.f;
	}

	void LevelMoveAction::endAction(
		std::vector<CellCollisionComponent>& collisionComponents)
	{
		collisionComponents[m_cellToDrop].areCollisionsActive = true;
		collisionComponents[m_cellToDrop].isFloorActive = true;
		m_actionState = ENDED;
	}

	LevelMoveAction::State LevelMoveAction::getCurrentActionState() const
	{
		return m_actionState;
	}

	void LevelMoveAction::setDropCellId(int id)
	{
		m_cellToDrop = id;
	}

	int LevelMoveAction::getDropCellId()
	{
		return m_cellToDrop;
	}

	void LevelMoveAction::addShiftCellId(int id)
	{
		m_cellsToShift.push_back(id);
	}

	void LevelMoveAction::setShiftAction(
		CellMoveComponent::State shiftAction)
	{
		m_shiftAction = shiftAction;
	}

	CellMoveComponent::State LevelMoveAction::getShiftAction() const
	{
		return m_shiftAction;
	}

	LevelMoveAction::LevelMoveAction(int rowOrColumn)
	{
		this->m_rowOrColumn = rowOrColumn;
		this->m_dropDelay = 4.f;
	}

	LevelMoveAction::LevelMoveAction(int rowOrColumn, float dropDelay)
	{
		this->m_rowOrColumn = rowOrColumn;
		this->m_dropDelay = dropDelay;
	}

	
	LevelMoveAction::~LevelMoveAction()
	{

	}
}