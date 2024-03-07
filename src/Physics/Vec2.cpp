#include "Physics/Vec2.h"

namespace Physics
{

	template <typename T>
	T Vec2<T>::length() const
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	template <typename T>
	T Vec2<T>::distance(const Vec2<T>& vector) const
	{
		return sqrt(
			pow(this->x - vector.x, 2) +
			pow(this->y - vector.y, 2)
		);
	}

	template <typename T>
	void Vec2<T>::applyRotation(T angle)
	{
		T cosAngle = cos(angle * this->m_pi / 180.);
		T sinAngle = sin(angle * this->m_pi / 180.);
		T newX = this->x * cosAngle - this->y * sinAngle;
		T newY = this->x * sinAngle + this->y * cosAngle;
		this->x = newX;
		this->y = newY;
	}

	template <typename T>
	Vec2<T> Vec2<T>::floor()
	{
		return Vec2<T>(std::floor(this->x),std::floor(this->y));
	}
	
	template <typename T>
	Vec2<T> Vec2<T>::operator + (const Vec2<T>& vector) const
	{
		return Vec2<T>(this->x + vector.x, this->y + vector.y);
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator + (T value) const
	{
		return Vec2<T>(this->x + value, this->y + value);
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator - (const Vec2<T>& vector) const
	{
		return Vec2<T>(this->x - vector.x, this->y - vector.y);
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator - (T value) const
	{
		return Vec2<T>(this->x - value, this->y - value);
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator * (T value) const
	{
		return Vec2<T>(this->x * value, this->y * value);
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator / (T value) const
	{
		return Vec2<T>(this->x / value, this->y / value);
	}

	template <typename T>
	void Vec2<T>::operator += (const Vec2<T>& vector)
	{
		this->x = this->x + vector.x;
		this->y = this->y + vector.y;
	}

	template <typename T>
	void Vec2<T>::operator -= (const Vec2<T>& vector)
	{
		this->x = this->x - vector.x;
		this->y = this->y - vector.y;
	}

	template <typename T>
	bool Vec2<T>::operator ==  (const Vec2<T>& vector) const
	{
		return this->x == vector.x &&
			this->y == vector.y;
	}

	template <typename T>
	Vec2<T>::Vec2(T xin, T yin)
	{
		this->x = xin;
		this->y = yin;
	}

	template <typename T>
	Vec2<T>::Vec2()
	{
		x = 0.f;
		y = 0.f;
	}
}

template class Physics::Vec2<float>;

template class Physics::Vec2<double>;

template class Physics::Vec2<int>;