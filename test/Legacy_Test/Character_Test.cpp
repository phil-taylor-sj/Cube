#include "../pch.h"
#include "Assets/Character.h"

namespace Character_Tests
{
	TEST(Character_setPosition_Inherited_Test, 
		Should_set_position_to_specified_values)
	{
		Character testCharacter_1 = Character();
		testCharacter_1.setPosition(10, 10);
		ASSERT_EQ(testCharacter_1.getPosition(), sf::Vector2f(10, 10));

		Character testCharacter_2 = Character();
		testCharacter_2.setPosition(30.5, 5.7);
		ASSERT_EQ(testCharacter_2.getPosition(), sf::Vector2f(30.5, 5.7));

		testCharacter_2.setPosition(10, 10);
		sf::Vector2f expectedPosition_3 = sf::Vector2f{10, 10};
		ASSERT_EQ(testCharacter_2.getPosition(), expectedPosition_3);
	}

	TEST(Character_Constructor_Inherited_Test, 
		Should_initailise_position_to_zero_value)
	{
		Character testCharacter = Character();
		sf::Vector2f expectedPosition = sf::Vector2f(0.0, 0.0);
		ASSERT_EQ(testCharacter.getPosition(), expectedPosition);
	}

	TEST(Character_Constructor_Test,
		Should_initailise_movement_speed_to_zero_value)
	{
		Character testCharacter = Character();
		float expectedMovementSpeed = 0;
		ASSERT_EQ(testCharacter.getMovementSpeed(), expectedMovementSpeed);
	}

	TEST(Character_setMovementSpeed_Test,
		Should_set_movement_speed_to_specified_value)
	{
		Character testCharacter_1 = Character();
		testCharacter_1.setMovementSpeed(20);
		float expectedMovementSpeed_1 = 20;
		ASSERT_EQ(testCharacter_1.getMovementSpeed(), expectedMovementSpeed_1);

		Character testCharacter_2 = Character();
		testCharacter_2.setMovementSpeed(512.25);
		float expectedMovementSpeed_2 = 512.25;
		ASSERT_EQ(testCharacter_2.getMovementSpeed(), expectedMovementSpeed_2);

		testCharacter_2.setMovementSpeed(-0.416);
		float expectedMovementSpeed_3 = -0.416;
		ASSERT_EQ(testCharacter_2.getMovementSpeed(), expectedMovementSpeed_3);
	}

	TEST(Character_setXxxxMovement_Test,
		each_function_should_set_movement_in_corresponding_direction)
	{
		Character testCharacter = Character();
		testCharacter.setMovementSpeed(1.0);
		
		testCharacter.setDownMovement(true);
		testCharacter.move(1.0);
		ASSERT_FLOAT_EQ(0.0, testCharacter.getPosition().x);
		ASSERT_FLOAT_EQ(1.0, testCharacter.getPosition().y);

		testCharacter.setRightMovement(true);
		testCharacter.move(1.0);
		ASSERT_FLOAT_EQ(0.7071068, testCharacter.getPosition().x);
		ASSERT_FLOAT_EQ(1.7071068, testCharacter.getPosition().y);

		testCharacter.setDownMovement(false);
		testCharacter.move(1.0);
		ASSERT_FLOAT_EQ(1.7071068, testCharacter.getPosition().x);
		ASSERT_FLOAT_EQ(1.7071068, testCharacter.getPosition().y);

		testCharacter.setUpMovement(true);
		testCharacter.setLeftMovement(true);
		testCharacter.move(1.0);
		ASSERT_FLOAT_EQ(1.0, testCharacter.getPosition().x);
		ASSERT_FLOAT_EQ(1.0, testCharacter.getPosition().y);

	}

}