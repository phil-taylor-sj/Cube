#include "../pch.h"
#include "../../src/Assets/Cell.cpp"

namespace Cell_Tests
{
	TEST(Cell_Constructor_Inherited_Test, Should_initailise_position_to_zero_value)
	{
		Cell testCell = Cell();
		sf::Vector2f expectedPosition = sf::Vector2f(0, 0);
		ASSERT_EQ(testCell.getPosition(), expectedPosition);

	}
	TEST(Cell_Constructor_Test, Should_initialise_indices_to_zero_value)
	{
		Cell testCell = Cell();
		sf::Vector2i expectedIndices = sf::Vector2i(0, 0);
		ASSERT_EQ(testCell.getCellIndices(), expectedIndices);
	}

	TEST(Cell_setCellIndicies, Should_set_indices_to_specified_values)
	{
		Cell testCell_1 = Cell();
		testCell_1.setCellIndices(10, 10);
		sf::Vector2i expectedIndices_1 = sf::Vector2i(10, 10);
		ASSERT_EQ(testCell_1.getCellIndices(), expectedIndices_1);

		Cell testCell_2 = Cell();
		testCell_2.setCellIndices(30, 5);
		sf::Vector2i expectedIndices_2 = sf::Vector2i(30, 5);
		ASSERT_EQ(testCell_2.getCellIndices(), expectedIndices_2);

		testCell_2.setCellIndices(10, 10);
		sf::Vector2i expectedIndices_3 = sf::Vector2i(10, 10);
		ASSERT_EQ(testCell_2.getCellIndices(), expectedIndices_3);
	}
}