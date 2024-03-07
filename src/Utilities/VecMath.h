#pragma once
#include "Physics/Vec2.h"
#include "Math.h"
#include <algorithm>

namespace Utilities
{
	template <typename T>
	class VecMath
	{
	public:
		static T angleBetweenVectors(
			Physics::Vec2f vectorOne, Physics::Vec2f vectorTwo);
		static T vectorMagnitude(Physics::Vec2f vector);
	};
}
