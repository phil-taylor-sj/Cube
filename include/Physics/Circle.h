#pragma once
#include <math.h>
#include "Physics/Vec2.h"

namespace Physics
{
	struct CircleParams {
		Vec2f position;
		float radius;
		float radiusSquared;
	};

	class Circle
	{
	public:
		void setPosition(Vec2f position);
		void setPosition(float xPosition, float yPosition);
		void setRadius(float radius);
		void scaleRadius(float scale);

		struct CircleParams getCircle();

		Circle();
		Circle(Vec2f position, float radius);
		Circle(float xPosition, float yPosition, float radius);
		~Circle();

	private:
		CircleParams m_params;
	};
}