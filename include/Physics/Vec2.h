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

		void applyRotation(T angle);

		Vec2<T> operator + (const Vec2<T>& vector);

		Vec2<T> operator + (T value);

		Vec2<T> operator - (const Vec2<T>& vector);

		Vec2<T> operator - (T value);

		Vec2<T> operator * (T value);
	
		void operator += (const Vec2<T>& vector);

		void operator -= (const Vec2<T>& vector);



		bool operator == (const Vec2<T>& vector) const
		{
			return this->x == vector.x &&
				this->y == vector.y;
		}

		Vec2();
		Vec2(T xin, T yin);

	private:
		double m_pi = 3.141592653589793;
	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;
}