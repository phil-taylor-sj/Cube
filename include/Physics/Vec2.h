#pragma once
#include "math.h"

namespace Physics
{
	template <typename T>
	class Vec2
	{

	public:
		T x;
		T y;

		T length() const;

		T distance(const Vec2<T>& vector) const;

		Vec2<T> operator + (Vec2<T> vector)
		{
			return Vec2<T>(this->x + vector.x, this->y + vector.y);
		}

		Vec2<T> operator - (Vec2<T> vector)
		{
			return Vec2<T>(this->x - vector.x, this->y - vector.y);
		}

		bool operator == (const Vec2<T>& vector) const
		{
			return this->x == vector.x &&
				this->y == vector.y;
		}

		Vec2();
		Vec2(T xin, T yin);

	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;
}