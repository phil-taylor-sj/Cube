#pragma once
#include "Physics/Vec2.h"
#include "Math.h"
#include <algorithm>

#include <VecPlus/Vec2.h>

namespace Utilities
{
	template <typename T>
	class VecMath
	{
	public:
		static T angleBetweenVectors(
			vecp::Vec2f vectorOne, vecp::Vec2f vectorTwo);
		static T vectorMagnitude(vecp::Vec2f vector);
	};
}
