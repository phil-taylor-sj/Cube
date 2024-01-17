#include "Physics/Circle.h"

namespace Physics
{
	void Circle::setPosition(Vec2f position)
	{
		m_params.previousPosition = m_params.position;
		m_params.position = position;
	}

	void Circle::setPosition(float xPosition, float yPosition)
	{
		m_params.previousPosition = m_params.position;
		m_params.position = Vec2f(xPosition, yPosition);
	}

	void Circle::translate(Vec2f deltaPosition)
	{
		m_params.previousPosition = m_params.position;
		m_params.position += deltaPosition;
	}

	void Circle::translate(float xPosition, float yPosition)
	{
		m_params.previousPosition = m_params.position;
		m_params.position.x += xPosition;
		m_params.position.y += yPosition;
	}

	void Circle::setRadius(float radius)
	{
		m_params.radius = radius;
		m_params.radiusSquared = pow(radius,2);
	}

	void Circle::scaleRadius(float scale)
	{
		m_params.radius = m_params.radius * scale;
		m_params.radiusSquared = pow(m_params.radius, 2);
	}

	void Circle::scalePosition(float scale)
	{
		m_params.previousPosition = m_params.previousPosition * scale;
		m_params.position = m_params.position * scale;
	}

	CircleParams Circle::getCircle() const
	{
		return m_params;
	}

	Circle::Circle()
	{
		m_params.position = Vec2f(0.f, 0.f);
		m_params.radius = 1.f;
		m_params.radiusSquared = 1.f;
	}


	Circle::Circle(Vec2f position, float radius)
	{
		m_params.position = position;
		m_params.radius = radius;
		m_params.radiusSquared = pow(radius, 2);
	}

	Circle::Circle(float xPosition, float yPosition, float radius)
	{
		m_params.position = Vec2f(xPosition, yPosition);
		m_params.radius = radius;
		m_params.radiusSquared = pow(radius, 2);
	}

	Circle::~Circle()
	{

	}
}