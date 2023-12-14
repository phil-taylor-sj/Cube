#include "../pch.h"
#include "Collision/Rectangle.h"

namespace Coll = Collision;

namespace Rectangle_Tests
{

	TEST(Rectangle_setPosition_Test,
		Vector_position_should_set_position_params_to_specified_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle();
		testRect_1.setPosition(sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(5.f, 3.f));
	}

	TEST(Rectangle_setPosition_Test,
		Float_position_should_set_position_params_to_specified_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle();
		testRect_1.setPosition(5.f, 3.f);
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(5.f, 3.f));
	}

	TEST(Rectangle_scaleWidthHeight_Test,
		Should_scale_width_and_height_by_specified_factor)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle(sf::Vector2f(5.f, 3.f), 9.f, 7.f);
		testRect_1.scaleWidthHeight(2.f);
		ASSERT_EQ(testRect_1.getWidth(), 18.f);
		ASSERT_EQ(testRect_1.getHeight(), 14.f);
		ASSERT_EQ(testRect_1.getHalfWidth(), 9.f);
		ASSERT_EQ(testRect_1.getHalfHeight(), 7.f);

		Coll::Rectangle testRect_2 = Coll::Rectangle(sf::Vector2f(5.f, 3.f), 9.f, 7.f);
		testRect_2.scaleWidthHeight(0.5f);
		ASSERT_EQ(testRect_2.getWidth(), 4.5f);
		ASSERT_EQ(testRect_2.getHeight(), 3.5f);
		ASSERT_EQ(testRect_2.getHalfWidth(), 2.25f);
		ASSERT_EQ(testRect_2.getHalfHeight(), 1.75f);
	}

	TEST(Rectangle_getRectangle_Test,
		Should_return_struct_of_rectangle_paramters)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle(sf::Vector2f(5.f, 3.f), 9.f, 7.f);
		testRect_1.setAngle(30.f);
		Coll::RectParams output = testRect_1.getRectangle();
		ASSERT_EQ(output.x, 5.f);
		ASSERT_EQ(output.y, 3.f);
		ASSERT_EQ(output.width, 9.f);
		ASSERT_EQ(output.height, 7.f);
		ASSERT_EQ(output.halfWidth, 4.5f);
		ASSERT_EQ(output.halfHeight, 3.5f);
		ASSERT_EQ(output.angle, 30.f);
	}

	TEST(Rectangle_Constructor_Test,
		Empty_arguments_should_set_all_params_t0_default_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle();
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(0.f, 0.f));
		ASSERT_EQ(testRect_1.getWidth(), 1.f);
		ASSERT_EQ(testRect_1.getHeight(), 1.f);
		ASSERT_EQ(testRect_1.getHalfWidth(), 0.5f);
		ASSERT_EQ(testRect_1.getHalfHeight(), 0.5f);
		ASSERT_EQ(testRect_1.getAngle(), 0.f);
	}

	TEST(Rectangle_Constructor_Test,
		Vector_position_should_set_position_params_to_specified_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle(sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testRect_1.getWidth(), 1.f);
		ASSERT_EQ(testRect_1.getHeight(), 1.f);
		ASSERT_EQ(testRect_1.getHalfWidth(), 0.5f);
		ASSERT_EQ(testRect_1.getHalfHeight(), 0.5f);
		ASSERT_EQ(testRect_1.getAngle(), 0.f);
	}

	TEST(Rectangle_Constructor_Test, 
		Float_position_should_set_position_params_to_specified_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle(5.f, 3.f);
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testRect_1.getWidth(), 1.f);
		ASSERT_EQ(testRect_1.getHeight(), 1.f);
		ASSERT_EQ(testRect_1.getHalfWidth(), 0.5f);
		ASSERT_EQ(testRect_1.getHalfHeight(), 0.5f);
		ASSERT_EQ(testRect_1.getAngle(), 0.f);
	}

	TEST(Rectangle_Constructor_Test, 
		Vecotor_position_and_float_dimensions_should_params_to_specified_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle(sf::Vector2f(5.f, 3.f), 9.f, 7.f);
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testRect_1.getWidth(), 9.f);
		ASSERT_EQ(testRect_1.getHeight(), 7.f);
		ASSERT_EQ(testRect_1.getHalfWidth(), 4.5f);
		ASSERT_EQ(testRect_1.getHalfHeight(), 3.5f);
		ASSERT_EQ(testRect_1.getAngle(), 0.f);
	}

	TEST(Rectangle_Constructor_Test, 
		Float_position_and_float_dimensions_should_params_to_specified_values)
	{
		Coll::Rectangle testRect_1 = Coll::Rectangle(5.f, 3.f, 9.f, 7.f);
		ASSERT_EQ(testRect_1.getPosition(), sf::Vector2f(5.f, 3.f));
		ASSERT_EQ(testRect_1.getWidth(), 9.f);
		ASSERT_EQ(testRect_1.getHeight(), 7.f);
		ASSERT_EQ(testRect_1.getHalfWidth(), 4.5f);
		ASSERT_EQ(testRect_1.getHalfHeight(), 3.5f);
		ASSERT_EQ(testRect_1.getAngle(), 0.f);
	}

}
