#pragma once
#include <cmath>
#include "Vec2.h"
#include "Circle.h"
#include "Rectangle.h"

namespace Physics
{
	class CollisionCorrections
	{
	public:
		static Vec2f getWallCorrection(
			CircleParams circle, RectParams wall);
	}; 
}