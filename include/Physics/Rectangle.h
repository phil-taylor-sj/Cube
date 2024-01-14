#pragma once
#include "Physics/Vec2.h"

namespace Physics
{
	struct RectParams {
		Vec2f position;
		Vec2f previousPosition;
		float width;
		float height;
		float halfWidth;
		float halfHeight;
		float angle;
	};

	class Rectangle
	{
	public:
		void setPosition(Vec2f position);
		void setPosition(float xPosition, float yPosition);
		void translate(Vec2f deltaPosition);
		void translate(float xDelta, float yDelta);
		void setWidth(float width);
		void setHeight(float height);
		void setAngle(float angle);
		void scaleWidthHeight(float scale);
		void scalePosition(float scale);

		struct RectParams getRectangle() const;

		Rectangle();
		Rectangle(Vec2f position);
		Rectangle(float xPosition, float yPosition);
		Rectangle(Vec2f position, float width, float height);
		Rectangle(
			float xPosition, float yPosition, 
			float width, float height
		);
		~Rectangle();

	private:
		RectParams m_params;
	};
}