#include "../pch.h"
#include "Physics/Rectangle.h"

namespace phys = Physics;

namespace Rectangle_Tests
{
	TEST(Rectangle_setPosition_Test,
		Vector_position_should_set_position_params_to_specified_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle();
		testRect_1.setPosition(vecp::Vec2f(5.f, 3.f));
		vecp::Vec2f output = testRect_1.getRectangle().position;
		ASSERT_EQ(output.x, 5.f);
		ASSERT_EQ(output.y, 3.f);

	}

	/**
	TEST(Rectangle_setPosition_Test,
		Float_position_should_set_position_params_to_specified_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle();
		testRect_1.setPosition(5.f, 3.f);
		ASSERT_EQ(testRect_1.getRectangle().position, vecp::Vec2f(5.f, 3.f));
	}

	TEST(Rectangle_scaleWidthHeight_Test,
		Should_scale_width_and_height_by_specified_factor)
	{
		phys::Rectangle testRect_1 = phys::Rectangle(vecp::Vec2f(5.f, 3.f), 9.f, 7.f);
		testRect_1.scaleWidthHeight(2.f);
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.width, 18.f);
		ASSERT_EQ(testParams_1.height, 14.f);
		ASSERT_EQ(testParams_1.halfWidth, 9.f);
		ASSERT_EQ(testParams_1.halfHeight, 7.f);

		phys::Rectangle testRect_2 = phys::Rectangle(vecp::Vec2f(5.f, 3.f), 9.f, 7.f);
		testRect_2.scaleWidthHeight(0.5f);
		phys::RectParams testParams_2 = testRect_2.getRectangle();
		ASSERT_EQ(testParams_2.width, 4.5f);
		ASSERT_EQ(testParams_2.height, 3.5f);
		ASSERT_EQ(testParams_2.halfWidth, 2.25f);
		ASSERT_EQ(testParams_2.halfHeight, 1.75f);
	}

	TEST(Rectangle_getRectangle_Test,
		Should_return_struct_of_rectangle_paramters)
	{
		phys::Rectangle testRect_1 = phys::Rectangle(vecp::Vec2f(5.f, 3.f), 9.f, 7.f);
		testRect_1.setAngle(30.f);
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.position.x, 5.f);
		ASSERT_EQ(testParams_1.position.y, 3.f);
		ASSERT_EQ(testParams_1.width, 9.f);
		ASSERT_EQ(testParams_1.height, 7.f);
		ASSERT_EQ(testParams_1.halfWidth, 4.5f);
		ASSERT_EQ(testParams_1.halfHeight, 3.5f);
		ASSERT_EQ(testParams_1.angle, 30.f);
	}

	TEST(Rectangle_Constructor_Test,
		Empty_arguments_should_set_all_params_to_default_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle();
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.position, vecp::Vec2f(0.f, 0.f));
		ASSERT_EQ(testParams_1.width, 1.f);
		ASSERT_EQ(testParams_1.height, 1.f);
		ASSERT_EQ(testParams_1.halfWidth, 0.5f);
		ASSERT_EQ(testParams_1.halfHeight, 0.5f);
		ASSERT_EQ(testParams_1.angle, 0.f);
	}

	TEST(Rectangle_Constructor_Test,
		Vector_position_should_set_position_params_to_specified_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle(vecp::Vec2f(5.f, 3.f));
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.position, phys::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.width, 1.f);
		ASSERT_EQ(testParams_1.height, 1.f);
		ASSERT_EQ(testParams_1.halfWidth, 0.5f);
		ASSERT_EQ(testParams_1.halfHeight, 0.5f);
		ASSERT_EQ(testParams_1.angle , 0.f);
	}

	TEST(Rectangle_Constructor_Test, 
		Float_position_should_set_position_params_to_specified_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle(5.f, 3.f);
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.position, vecp::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.width, 1.f);
		ASSERT_EQ(testParams_1.height, 1.f);
		ASSERT_EQ(testParams_1.halfWidth, 0.5f);
		ASSERT_EQ(testParams_1.halfHeight, 0.5f);
		ASSERT_EQ(testParams_1.angle, 0.f);
	}

	TEST(Rectangle_Constructor_Test, 
		Vecotor_position_and_float_dimensions_should_params_to_specified_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle(vecp::Vec2f(5.f, 3.f), 9.f, 7.f);
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.position, vecp::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.width, 9.f);
		ASSERT_EQ(testParams_1.height, 7.f);
		ASSERT_EQ(testParams_1.halfWidth, 4.5f);
		ASSERT_EQ(testParams_1.halfHeight, 3.5f);
		ASSERT_EQ(testParams_1.angle, 0.f);
	}

	TEST(Rectangle_Constructor_Test, 
		Float_position_and_float_dimensions_should_params_to_specified_values)
	{
		phys::Rectangle testRect_1 = phys::Rectangle(5.f, 3.f, 9.f, 7.f);
		phys::RectParams testParams_1 = testRect_1.getRectangle();
		ASSERT_EQ(testParams_1.position, vecp::Vec2f(5.f, 3.f));
		ASSERT_EQ(testParams_1.width, 9.f);
		ASSERT_EQ(testParams_1.height, 7.f);
		ASSERT_EQ(testParams_1.halfWidth, 4.5f);
		ASSERT_EQ(testParams_1.halfHeight, 3.5f);
		ASSERT_EQ(testParams_1.angle, 0.f);
	}
	*/
}
