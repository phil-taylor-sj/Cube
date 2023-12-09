#include "../pch.h"
#include "../../src/Assets/SpriteAsset.cpp"

namespace SpriteAsset_Tests
{
	TEST(SpriteAsset_Constructor_Test, Should_initialise_position_to_default_zero_values)
	{
		SpriteAsset testSprite = SpriteAsset();
		sf::Vector2f expectedPosition = sf::Vector2f(0, 0);
		ASSERT_EQ(testSprite.getPosition(), expectedPosition);
	}
}