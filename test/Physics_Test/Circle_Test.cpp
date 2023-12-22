#include "../pch.h"
#include "Physics/Circle.h"

namespace phys = Physics;

namespace Circle_Tests
{
	TEST(Circle_Constructor_Test,
		Empty_arguments_should_set_position_to_default_values)
	{
		phys::Circle testCircle_1 = phys::Circle();
		phys::CircleParams testParams_1 = testCircle_1.getCircle();
		ASSERT_EQ(testParams_1.position, phys::Vec2f(0.f, 0.f));
		ASSERT_EQ(testParams_1.radius, 1.f);
		ASSERT_EQ(testParams_1.radiusSquared, 1.f);
	}

	TEST(Circle_Constructor_Test,
		Vector2f_argument_should_set_position_and_radius_to_specified_values)
	{
		phys::Circle testCircle_1 = phys::Circle(phys::Vec2f(5.f, 3.f), 2.5f);
		phys::CircleParams testParams_1 = testCircle_1.getCircle();
		ASSERT_EQ(testParams_1.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.radius, 2.5f);
		ASSERT_EQ(testParams_1.radiusSquared, 6.25f);
	}

	TEST(Circle_Constructor_Test,
		Float_arguments_should_set_position_and_radius_to_specified_values)
	{
		phys::Circle testCircle_1 = phys::Circle(5.f, 3.f, 2.5f);
		phys::CircleParams testParams_1 = testCircle_1.getCircle();
		ASSERT_EQ(testParams_1.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.radius, 2.5f);
		ASSERT_EQ(testParams_1.radiusSquared, 6.25f);
	}

	TEST(Circle_getCircle_Test,
		Should_return_struct_of_circle_parameters)
	{
		phys::Circle testCircle_1 = phys::Circle(5.f, 3.f, 2.5f);
		phys::CircleParams testParams_1 = testCircle_1.getCircle();
		ASSERT_EQ(testParams_1.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.radius, 2.5f);
		ASSERT_EQ(testParams_1.radiusSquared, 6.25f);
	}

	TEST(Circle_scaleRadius_test,
		Should_scale_radius_and_radiusSquared_by_scale_factor)
	{
		phys::Circle testCircle_1 = phys::Circle(5.f, 3.f, 2.5f);
		testCircle_1.scaleRadius(2.f);
		phys::CircleParams testParams_1 = testCircle_1.getCircle();
		ASSERT_EQ(testParams_1.radius, 5.f);
		ASSERT_EQ(testParams_1.radiusSquared, 25.f);

		phys::Circle testCircle_2 = phys::Circle(5.f, 3.f, 2.5f);
		testCircle_2.scaleRadius(0.5f);
		phys::CircleParams testParams_2 = testCircle_2.getCircle();
		ASSERT_EQ(testParams_2.radius, 1.25f);
		ASSERT_EQ(testParams_2.radiusSquared, 1.5625f);
	}

}