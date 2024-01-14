#pragma once
#include <math.h>
#include "Physics/Vec2.h"

namespace Physics
{
	struct CircleParams {
		Vec2f position;
		Vec2f previousPosition;
		float radius;
		float radiusSquared;
	};

	class Circle
	{
	public:
		void setPosition(Vec2f position);
		void setPosition(float xPosition, float yPosition);
		void translate(Vec2f deltaPosition);
		void translate(float xDelta, float yDelta);
		void setRadius(float radius);
		void scaleRadius(float scale);
		void scalePosition(float scale);

		struct CircleParams getCircle() const;

		Circle();
		Circle(Vec2f position, float radius);
		Circle(float xPosition, float yPosition, float radius);
		~Circle();

	private:
		CircleParams m_params;
	};
}