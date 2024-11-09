#include "Physics/CollisionCorrections.h"

namespace Physics
{
	vecp::Vec2f CollisionCorrections::getWallCorrection(
		CircleParams circle, RectParams wall)
	{
		circle.position -= wall.position;
		circle.previousPosition -= wall.position;
		wall.previousPosition -= wall.position;
		wall.position = vecp::Vec2f(0.f, 0.f);
		float sign = 1.f;

		if (abs(circle.position.x) <= wall.halfWidth)
		{
			if (circle.position.y != 0.f)
			{
				sign = circle.position.y / abs(circle.position.y);
			}
			return vecp::Vec2f(
				0.f,
				sign * (wall.halfHeight + circle.radius) - circle.position.y
			);
		}

		if (abs(circle.position.y) <= wall.halfHeight)
		{
			if (circle.position.x != 0.f)
			{
				sign = circle.position.x / abs(circle.position.x);
			}
			return vecp::Vec2f(
				sign * (wall.halfWidth + circle.radius) - circle.position.x,
				0.f
			);
		}

		return vecp::Vec2f(0.f, 0.f);

		
	}
}