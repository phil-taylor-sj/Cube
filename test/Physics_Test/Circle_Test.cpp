#include "../pch.h"
#include "Physics/Circle.h"

namespace phys = Physics;

namespace Circle_Tests
{
	TEST(Circle_Constructor_Test,
		Empty_arguments_should_set_position_to_default_values)
	{
		phys::Circle circleOne = phys::Circle();
		phys::CircleParams paramsOne = circleOne.getCircle();
		ASSERT_EQ(paramsOne.position, phys::Vec2f(0.f, 0.f));
		ASSERT_EQ(paramsOne.radius, 1.f);
		ASSERT_EQ(paramsOne.radiusSquared, 1.f);
	}

	TEST(Circle_Constructor_Test,
		Vec2f_argument_should_set_position_and_radius_to_specified_values)
	{
		phys::Circle circleOne = phys::Circle(phys::Vec2f(5.f, 3.f), 2.5f);
		phys::CircleParams paramsOne = circleOne.getCircle();
		ASSERT_EQ(paramsOne.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(paramsOne.radius, 2.5f);
		ASSERT_EQ(paramsOne.radiusSquared, 6.25f);
	}

	TEST(Circle_Constructor_Test,
		Float_arguments_should_set_position_and_radius_to_specified_values)
	{
		phys::Circle circleOne = phys::Circle(5.f, 3.f, 2.5f);
		phys::CircleParams paramsOne = circleOne.getCircle();
		ASSERT_EQ(paramsOne.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(paramsOne.radius, 2.5f);
		ASSERT_EQ(paramsOne.radiusSquared, 6.25f);
	}

	TEST(Circle_getCircle_Test,
		Should_return_struct_of_circle_parameters)
	{
		phys::Circle circleOne = phys::Circle(5.f, 3.f, 2.5f);
		phys::CircleParams paramsOne = circleOne.getCircle();
		ASSERT_EQ(paramsOne.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(paramsOne.radius, 2.5f);
		ASSERT_EQ(paramsOne.radiusSquared, 6.25f);
	}

	TEST(Circle_scaleRadius_test,
		Should_scale_radius_and_radiusSquared_by_scale_factor)
	{
		phys::Circle circleOne = phys::Circle(5.f, 3.f, 2.5f);
		circleOne.scaleRadius(2.f);
		phys::CircleParams paramsOne = circleOne.getCircle();
		ASSERT_EQ(paramsOne.radius, 5.f);
		ASSERT_EQ(paramsOne.radiusSquared, 25.f);

		phys::Circle circleTwo = phys::Circle(5.f, 3.f, 2.5f);
		circleTwo.scaleRadius(0.5f);
		phys::CircleParams paramsTwo = circleTwo.getCircle();
		ASSERT_EQ(paramsTwo.radius, 1.25f);
		ASSERT_EQ(paramsTwo.radiusSquared, 1.5625f);
	}

}