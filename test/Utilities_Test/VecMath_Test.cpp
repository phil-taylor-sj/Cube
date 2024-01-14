#include "../pch.h"
#include "Utilities/VecMath.h"

namespace VecMath_Tests
{
	TEST(VecMath_angleBetweenVectors_Test,
		Return_the_correct_angle_for_two_non_zero_vectors)
	{
		Physics::Vec2f vectorBase = Physics::Vec2f(1.f, 0.f);
		Physics::Vec2f vectorOne = Physics::Vec2f(1.f, 1.f);
		Physics::Vec2f vectorTwo = Physics::Vec2f(-1.f, 1.f);
		Physics::Vec2f vectorThree = Physics::Vec2f(-1.f, -1.f);

		float resultOne = Utilities::VecMath<float>::angleBetweenVectors(
			vectorBase, vectorOne
		);
		float resultTwo = Utilities::VecMath<float>::angleBetweenVectors(
			vectorBase, vectorTwo
		);
		float resultThree = Utilities::VecMath<float>::angleBetweenVectors(
			vectorBase, vectorThree
		);

		float tolerance = 1e-4;
		EXPECT_NEAR(resultOne, 45., tolerance);
		EXPECT_NEAR(resultTwo, 135., tolerance);
		EXPECT_NEAR(resultThree, 135., tolerance);
	}
	
}