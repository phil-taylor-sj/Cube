#include "Utilities/VecMath.h"

namespace Utilities
{
	template <typename T>
	T VecMath<T>::angleBetweenVectors(
		Physics::Vec2f vectorOne, Physics::Vec2f vectorTwo
	)
	{
		double dotProduct = (vectorOne.x * vectorTwo.x) + (vectorOne.y * vectorTwo.y);
		double magnitude = VecMath::vectorMagnitude(vectorOne) 
			* VecMath::vectorMagnitude(vectorTwo);
		if (magnitude != 0.)
		{
			T angle = acos(
				std::max(std::min(dotProduct / magnitude, 1.), -1.)
			) * 180.f / 3.14159265359;
			return angle;
		}
		else
		{
			return 0.;
		}
	}

	template <typename T>
	T VecMath<T>::vectorMagnitude(
		Physics::Vec2f vector
	)
	{
		return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	}
}

template class Utilities::VecMath<float>;

template class Utilities::VecMath<double>;