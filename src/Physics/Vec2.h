#pragma once
#include <cmath>

namespace Physics
{
	/**
	 * @brief Represents a 2D vector with components of type T.
	 *
	 * This class provides basic operations for 2D vectors such as
	 * length calculation, distance calculation, rotation, and various
	 * arithmetic operations.
	 *
	 * @tparam T The type of elements in the vector (e.g., float, double, int).
	 */
	template <typename T>
	class Vec2
	{

	public:
		T x; ///< The x-coordinate of the vector.
		T y; ///< The y-coordinate of the vector.
		
		/**
		 * @brief Calculate the length (magnitude) of the vector.
		 * 
		 * @return The length of the vector.
		 */
		T length() const;

		/**
		 * @brief Calculate the distance between this vector and another vector.
		 *
		 * @param vector The other vector to calculate the distance to.
		 * @return The distance between this vector and the other vector.
		 */
		T distance(const Vec2<T>& vector) const;

		/**
		 * @brief Apply a rotation to the vector by a given angle (in degrees).
		 *
		 * @param angle The angle (in degrees) by which to rotate the vector.
		 */
		void applyRotation(T angle);

		/**
		 * @brief Round each component down to the nearest integer.
		 */
		Vec2<T> floor();

		void copy(const Vec2<T>& vector);

		/**
		 * @brief Overload the addition operator (+) for vector addition.
		 * 
		 * @param vector The vector to be added.
		 * @return The result of vector addition.
		 */
		Vec2<T> operator + (const Vec2<T>& vector) const;

		/**
		 * @brief Overload the addition operator (+) for adding a scalar value.
		 * 
		 * @param value The scalar value to be added.
		 * @return The result of adding the scalar value.
		 */
		Vec2<T> operator + (T value) const;

		/**
		 * @brief Overload the subtraction operator (-) for vector subtraction.
		 * 
		 * @param vector The vector to be subtracted.
		 * @return The result of vector subtraction.
		 */
		Vec2<T> operator - (const Vec2<T>& vector) const;

		/**
		 * @brief Overload the subtraction operator (-) for subtracting a scalar value.
		 * 
		 * @param value The scalar value to be subtracted.
		 * @return The result of subtracting the scalar value.
		 */
		Vec2<T> operator - (T value) const;

		/**
		 * @brief Overload the multiplication operator (*) for scalar multiplication.
		 * 
		 * @param value The scalar value to be multiplied.
		 * @return The result of scalar multiplication.
		 */
		Vec2<T> operator * (T value) const;
	
		/**
		 * @brief Overload the division operator (/) for scalar division.
		 *
		 * @param value The scalar value to be divided by.
		 * @return The result of scalar division.
		 */
		Vec2<T> operator / (T value) const;

		/**
		 * @brief Overload the addition assignment operator (+=) for vector addition.
		 * 
		 * @param vector The vector to be added.
		 */
		void operator += (const Vec2<T>& vector);

		/**
		 * @brief Overload the subtraction assignment operator (-=) for vector subtraction.
		 * 
		 * @param vector The vector to be subtracted.
		 */
		void operator -= (const Vec2<T>& vector);

		/**
		 * @brief Overload the equality operator (==) for vector comparison.
		 * 
		 * @param vector The vector to compare with.
		 * @return True if the vectors are equal, false otherwise.
		 */

		bool operator == (const Vec2<T>& vector) const;

		/**
		 * @brief Construct a new Vec2 object with both components initialized to 0.
		 */
		Vec2();

		/**
		 * @brief Construct a new Vec2 object with given x and y components.
	     *
		 * @param xin The x component of the vector.
		 * @param yin The y component of the vector.
		 */
		Vec2(T xin, T yin);

	private:
		double m_pi = 3.141592653589793; ///< A constant value for pi.
	};

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;
}