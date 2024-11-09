#include "Levels/CellStaticRectangle.h"

namespace Levels
{
	void CellStaticRectangle ::setRelativePosition(float relativeX, float relativeY)
	{
		m_relativePosition = vecp::Vec2f(relativeX, relativeY);
	}

	void CellStaticRectangle::setRelativePosition(vecp::Vec2f relativePosition)
	{
		m_relativePosition = relativePosition;
	}

	void CellStaticRectangle::setRelativeDimensions(float relativeWidth, float relativeHeight)
	{
		m_relativeWidth = relativeWidth;
		m_relativeHeight = relativeHeight;
	}

	void CellStaticRectangle::setAngle(float angle)
	{
		m_rectangle.setAngle(angle);
	}

	void CellStaticRectangle::setCellWidth(float width)
	{
		m_cellWidth = width;
		m_updateRectangle();
	}

	void CellStaticRectangle::setCellPosition(float xPosition, float yPosition)
	{
		m_cellPosition = vecp::Vec2f(xPosition, yPosition);
		m_updateRectangle();
	}

	void CellStaticRectangle::setCellPosition(vecp::Vec2f position)
	{
		m_cellPosition = position;
		m_updateRectangle();
	}

	Physics::RectParams CellStaticRectangle::getRectangle() const
	{
		return m_rectangle.getRectangle();
	}

	CellStaticRectangle::CellStaticRectangle()
	{
		m_cellWidth = 10.f;
		m_cellPosition = vecp::Vec2f(10.f, 10.f);
		m_relativePosition = vecp::Vec2f(0.5f, 0.5f);
		m_relativeWidth = 0.1f;
		m_relativeHeight = 0.1f;
		m_angle = 0.f;
		m_updateRectangle();
	}

	CellStaticRectangle::~CellStaticRectangle()
	{

	}

	void CellStaticRectangle::m_updateRectangle()
	{
		m_rectangle.setPosition(
			m_cellPosition.x + m_relativePosition.x * m_cellWidth,
			m_cellPosition.y + m_relativePosition.y * m_cellWidth
		);
		m_rectangle.setWidth(m_relativeWidth * m_cellWidth);
		m_rectangle.setHeight(m_relativeHeight * m_cellWidth);
	}
}