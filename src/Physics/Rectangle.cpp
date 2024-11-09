#include "Physics/Rectangle.h"

namespace Physics
{
	void Rectangle::setPosition(vecp::Vec2f position)
	{
		m_params.previousPosition = m_params.position;
		m_params.position = position;
	}

	void Rectangle::setPosition(float xPosition, float yPosition)
	{
		m_params.previousPosition = m_params.position;
		m_params.position = vecp::Vec2f(xPosition, yPosition);
	}

	void Rectangle::translate(vecp::Vec2f deltaPosition)
	{
		m_params.previousPosition = m_params.position;
		m_params.position += deltaPosition;

	}

	void Rectangle::translate(float xDelta, float yDelta)
	{
		m_params.previousPosition = m_params.position;
		m_params.position.x += xDelta;
		m_params.position.y += yDelta;
	}

	void Rectangle::setWidth(float width)
	{
		m_params.width = width;
		m_params.halfWidth = 0.5 * width;
	}

	void Rectangle::setHeight(float height)
	{
		m_params.height = height;
		m_params.halfHeight = 0.5 * height;
	}

	void Rectangle::setAngle(float angle)
	{
		m_params.angle = angle;
	}

	void Rectangle::scaleWidthHeight(float scale)
	{
		m_params.width = m_params.width * scale;
		m_params.height = m_params.height * scale;
		m_params.halfWidth = 0.5f * m_params.width;
		m_params.halfHeight = 0.5f * m_params.height;
	}

	void Rectangle::scalePosition(float scale)
	{
		m_params.previousPosition = m_params.previousPosition * scale;
		m_params.position = m_params.position * scale;
	}

	RectParams Rectangle::getRectangle() const
	{
		return m_params;
	}

	Rectangle::Rectangle()
	{
		m_params.position = vecp::Vec2f(0.f, 0.f);
		m_params.angle = 0.f;
		this->setWidth(1.f);
		this->setHeight(1.f);
	}

	Rectangle::Rectangle(vecp::Vec2f position)
	{
		m_params.position = position;
		m_params.angle = 0.f;
		this->setWidth(1.f);
		this->setHeight(1.f);
	}

	Rectangle::Rectangle(float xPosition, float yPosition)
	{
		m_params.position = vecp::Vec2f(xPosition, yPosition);
		m_params.angle = 0.f;
		this->setWidth(1.f);
		this->setHeight(1.f);
	}

	Rectangle::Rectangle(vecp::Vec2f position, float width, float height)
	{
		m_params.position = position;
		m_params.angle = 0.f;
		this->setWidth(width);
		this->setHeight(height);
	}

	Rectangle::Rectangle(
		float xPosition, float yPosition, 
		float width, float height
	)
	{
		m_params.position = vecp::Vec2f(xPosition, yPosition);
		m_params.angle = 0.f;
		this->setWidth(width);
		this->setHeight(height);
	}

	Rectangle::~Rectangle()
	{

	}
}