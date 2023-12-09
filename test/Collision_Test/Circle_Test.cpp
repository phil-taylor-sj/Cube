#include "../pch.h"
#include "../../src/Collision/Circle.cpp"

namespace Coll = Collision;

namespace Circle_Tests
{
	TEST(Circle_Constructor_Test,
		Empty_arguments_should_set_position_to_default_values)
	{
		Coll::Circle testCircle_1 = Coll::Circle();
		ASSERT_EQ(testCircle_1.getPosition(), sf::Vector2f(0.f, 0.f));
		ASSERT_EQ(testCircle_1.getRadius(), 1.f);
		ASSERT_EQ(testCircle_1.getRadiusSquared(), 1.f);
	}

	TEST(Circle_Constructor_Test,
		Vector2f_argument_should_set_position_and_radius_to_specified_values)
	{
		Coll::Circle testCircle_1 = Coll::Circle(sf::Vector2f(5.f, 3.f), 2.5f);
		ASSERT_EQ(testCircle_1.getPosition(), sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testCircle_1.getRadius(), 2.5f);
		ASSERT_EQ(testCircle_1.getRadiusSquared(), 6.25f);
	}

	TEST(Circle_Constructor_Test,
		Float_arguments_should_set_position_and_radius_to_specified_values)
	{
		Coll::Circle testCircle_1 = Coll::Circle(5.f, 3.f, 2.5f);
		ASSERT_EQ(testCircle_1.getPosition(), sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testCircle_1.getRadius(), 2.5f);
		ASSERT_EQ(testCircle_1.getRadiusSquared(), 6.25f);
	}

	TEST(Circle_getCircle_Test,
		Should_return_struct_of_circle_parameters)
	{
		Coll::Circle testCircle_1 = Coll::Circle(5.f, 3.f, 2.5f);
		Coll::CircleParams output_1 = testCircle_1.getCircle();
		ASSERT_EQ(output_1.x, 5.f);
		ASSERT_EQ(output_1.y, 3.f);
		ASSERT_EQ(output_1.radius, 2.5f);
		ASSERT_EQ(output_1.radiusSquared, 6.25f);
	}

	TEST(Circle_scaleRadius_test,
		Should_scale_radius_and_radiusSquared_by_scale_factor)
	{
		Coll::Circle testCircle_1 = Coll::Circle(5.f, 3.f, 2.5f);
		testCircle_1.scaleRadius(2.f);
		ASSERT_EQ(testCircle_1.getRadius(), 5.f);
		ASSERT_EQ(testCircle_1.getRadiusSquared(), 25.f);

		Coll::Circle testCircle_2 = Coll::Circle(5.f, 3.f, 2.5f);
		testCircle_2.scaleRadius(0.5f);
		ASSERT_EQ(testCircle_2.getRadius(), 1.25f);
		ASSERT_EQ(testCircle_2.getRadiusSquared(), 1.5625f);
	}



}