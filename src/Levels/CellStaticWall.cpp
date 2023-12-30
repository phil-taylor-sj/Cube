#include "Levels/CellStaticWall.h"

namespace Levels
{
	void CellStaticWall ::setRelativePosition(float relativeX, float relativeY)
	{
		m_relativePosition = Physics::Vec2f(relativeX, relativeY);
	}

	void CellStaticWall::setRelativePosition(Physics::Vec2f relativePosition)
	{
		m_relativePosition = relativePosition;
	}

	void CellStaticWall::setRelativeDimensions(float relativeWidth, float relativeHeight)
	{
		m_relativeWidth = relativeWidth;
		m_relativeHeight = relativeHeight;
	}

	void CellStaticWall::setAngle(float angle)
	{
		m_rectangle.setAngle(angle);
	}

	void CellStaticWall::setCellWidth(float width)
	{
		m_cellWidth = width;
		m_updateRectangle();
	}

	void CellStaticWall::setCellPosition(float xPosition, float yPosition)
	{
		m_cellPosition = Physics::Vec2f(xPosition, yPosition);
		m_updateRectangle();
	}

	void CellStaticWall::setCellPosition(Physics::Vec2f position)
	{
		m_cellPosition = position;
		m_updateRectangle();
	}

	Physics::RectParams CellStaticWall::getRectangle()
	{
		return m_rectangle.getRectangle();
	}

	CellStaticWall::CellStaticWall()
	{
		m_cellWidth = 10.f;
		m_cellPosition = Physics::Vec2f(10.f, 10.f);
		m_relativePosition = Physics::Vec2f(0.5f, 0.5f);
		m_relativeWidth = 0.1f;
		m_relativeHeight = 0.1f;
		m_angle = 0.f;
		m_updateRectangle();
	}

	CellStaticWall::~CellStaticWall()
	{

	}

	void CellStaticWall::m_updateRectangle()
	{
		m_rectangle.setPosition(
			m_cellPosition.x + m_relativePosition.x * m_cellWidth,
			m_cellPosition.y + m_relativePosition.y * m_cellWidth
		);
		m_rectangle.setWidth(m_relativeWidth * m_cellWidth);
		m_rectangle.setHeight(m_relativeHeight * m_cellWidth);
	}
}