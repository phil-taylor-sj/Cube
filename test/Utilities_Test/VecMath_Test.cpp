#include "../pch.h"
#include "Utilities/VecMath.h"

namespace VecMath_Tests
{
	TEST(VecMath_angleBetweenVectors_Test,
		Return_the_correct_angle_for_two_non_zero_vectors)
	{
		vecp::Vec2f vectorBase = vecp::Vec2f(1.f, 0.f);
		vecp::Vec2f vectorOne = vecp::Vec2f(1.f, 1.f);
		vecp::Vec2f vectorTwo = vecp::Vec2f(-1.f, 1.f);
		vecp::Vec2f vectorThree = vecp::Vec2f(-1.f, -1.f);

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