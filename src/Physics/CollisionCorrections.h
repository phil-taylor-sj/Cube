#pragma once
#include <cmath>
#include <VecPlus/Vec2.h>

#include "Vec2.h"
#include "Circle.h"
#include "Rectangle.h"

namespace Physics
{
	/**
	 * @class CollisionCorrections
	 * @brief A class that provides methods for correcting collision interactions.
	 */
	class CollisionCorrections
	{
	public:
		/**
		 * @brief Calculate the correction vector for a circle-wall collision.
		 * @param circle The parameters of the circle.
		 * @param wall The parameters of the wall (rectangle).
		 * @return The correction vector to resolve the collision.
		 *
		 * This method calculates and returns the correction vector needed to resolve
		 * a collision between a circle and a wall (rectangle). The circle's position
		 * and previous position, as well as the wall's position, are adjusted to be
		 * relative to the wall's local coordinate system. Depending on the collision
		 * scenario, it returns the necessary correction vector to prevent overlap.
		 */
		static vecp::Vec2f getWallCorrection(
			CircleParams circle, RectParams wall);
	}; 
}