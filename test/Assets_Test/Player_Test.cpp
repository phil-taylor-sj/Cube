#include "../pch.h"
#include "../../src/Assets/Player.cpp"

namespace Player_Tests
{
	TEST(Player_setPosition_Inherited_Test,
		Should_set_position_to_specified_values)
	{
		Player testPlayer_1 = Player();
		testPlayer_1.setPosition(10, 10);
		ASSERT_EQ(testPlayer_1.getPosition(), sf::Vector2f(10, 10));

		Player testPlayer_2 = Player();
		testPlayer_2.setPosition(30.5, 5.7);
		ASSERT_EQ(testPlayer_2.getPosition(), sf::Vector2f(30.5, 5.7));

		testPlayer_2.setPosition(10, 10);
		sf::Vector2f expectedPosition_3 = sf::Vector2f{ 10, 10 };
		ASSERT_EQ(testPlayer_2.getPosition(), expectedPosition_3);
	}

	TEST(Player_Constructor_Inherited_Test,
		Should_initailise_position_to_zero_value)
	{
		Player testPlayer = Player();
		sf::Vector2f expectedPosition = sf::Vector2f(0.0, 0.0);
		ASSERT_EQ(testPlayer.getPosition(), expectedPosition);
	}

	TEST(Player_Constructor_Inherited_Test,
		Should_initailise_movement_speed_to_zero_value)
	{
		Player testPlayer = Player();
		float expectedMovementSpeed = 0;
		ASSERT_EQ(testPlayer.getMovementSpeed(), expectedMovementSpeed);
	}

	TEST(Player_setMovementSpeed_Inherited_Test,
		Should_set_movement_speed_to_specified_value)
	{
		Player testPlayer_1 = Player();
		testPlayer_1.setMovementSpeed(20);
		float expectedMovementSpeed_1 = 20;
		ASSERT_EQ(testPlayer_1.getMovementSpeed(), expectedMovementSpeed_1);

		Player testPlayer_2 = Player();
		testPlayer_2.setMovementSpeed(512.25);
		float expectedMovementSpeed_2 = 512.25;
		ASSERT_EQ(testPlayer_2.getMovementSpeed(), expectedMovementSpeed_2);

		testPlayer_2.setMovementSpeed(-0.416);
		float expectedMovementSpeed_3 = -0.416;
		ASSERT_EQ(testPlayer_2.getMovementSpeed(), expectedMovementSpeed_3);
	}

	TEST(Player_setXxxxMovement_Inherited_Test,
		Each_function_should_set_movement_in_corresponding_direction)
	{
		Player testPlayer = Player();
		testPlayer.setMovementSpeed(1.0);

		testPlayer.setDownMovement(true);
		testPlayer.move(1.0);
		ASSERT_FLOAT_EQ(0.0, testPlayer.getPosition().x);
		ASSERT_FLOAT_EQ(1.0, testPlayer.getPosition().y);

		testPlayer.setRightMovement(true);
		testPlayer.move(1.0);
		ASSERT_FLOAT_EQ(0.7071068, testPlayer.getPosition().x);
		ASSERT_FLOAT_EQ(1.7071068, testPlayer.getPosition().y);

		testPlayer.setDownMovement(false);
		testPlayer.move(1.0);
		ASSERT_FLOAT_EQ(1.7071068, testPlayer.getPosition().x);
		ASSERT_FLOAT_EQ(1.7071068, testPlayer.getPosition().y);

		testPlayer.setUpMovement(true);
		testPlayer.setLeftMovement(true);
		testPlayer.move(1.0);
		ASSERT_FLOAT_EQ(1.0, testPlayer.getPosition().x);
		ASSERT_FLOAT_EQ(1.0, testPlayer.getPosition().y);

	}
}