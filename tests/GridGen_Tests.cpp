#include "pch.h"
#include "../src/Utilities/GridGen.cpp"

namespace GridGen_Tests
{ 
	TEST(GridGen_randomiseGridColours_Test, 
		Return_a_2D_array_of_the_specified_size) 
	{
		std::vector<std::vector<std::string>> randomGridColours;

		randomGridColours = GridGen::randomiseGridColours(1, 1);
		ASSERT_EQ(randomGridColours.size() , 1);
		for (std::vector<std::string>& row : randomGridColours)
		{
			ASSERT_EQ(row.size(), 1);
		}

		randomGridColours = GridGen::randomiseGridColours(4, 4);
		ASSERT_EQ(randomGridColours.size(), 4);
		for (std::vector<std::string>& row : randomGridColours)
		{
			ASSERT_EQ(row.size(), 4);
		}

		randomGridColours = GridGen::randomiseGridColours(30, 30);
		ASSERT_EQ(randomGridColours.size(), 30);
		for (std::vector<std::string>& row : randomGridColours)
		{
			ASSERT_EQ(row.size(), 30);
		}

		randomGridColours = GridGen::randomiseGridColours(10, 35);
		ASSERT_EQ(randomGridColours.size(), 10);
		for (std::vector<std::string>& row : randomGridColours)
		{
			ASSERT_EQ(row.size(), 35);
		}
	}

	TEST(GridGen_randomiseGridColours_Test, 
		Returned_array_contains_no_matching_colours_in_adjacent_cells)
	{
		std::vector<std::vector<std::string>> randomGridColours;

		randomGridColours = GridGen::randomiseGridColours(4, 4);
		for (int i = 1; i < 4; i++)
		{
			ASSERT_NE(
				randomGridColours[i][0], randomGridColours[i - 1][0]);
		}
		for (int j = 1; j < 4; j++)
		{
			ASSERT_NE(
				randomGridColours[0][j], randomGridColours[0][j - 1]);
		}
		for (int i = 1; i < 4; i++) {
			for (int j = 1; j < 4; j++)
			{
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i - 1][j]);
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i][j - 1]);
			}
		}

		randomGridColours = GridGen::randomiseGridColours(30, 30);
		for (int i = 1; i < 30; i++)
		{
			ASSERT_NE(
				randomGridColours[i][0], randomGridColours[i - 1][0]);
		}
		for (int j = 1; j < 30; j++)
		{
			ASSERT_NE(
				randomGridColours[0][j], randomGridColours[0][j - 1]);
		}
		for (int i = 1; i < 30; i++) {
			for (int j = 1; j < 30; j++)
			{
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i - 1][j]);
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i][j - 1]);
			}
		}
		randomGridColours = GridGen::randomiseGridColours(25, 8);
		for (int i = 1; i < 25; i++)
		{
			ASSERT_NE(
				randomGridColours[i][0], randomGridColours[i - 1][0]);
		}
		for (int j = 1; j < 8; j++)
		{
			ASSERT_NE(
				randomGridColours[0][j], randomGridColours[0][j - 1]);
		}
		for (int i = 1; i < 25; i++) {
			for (int j = 1; j < 8; j++)
			{
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i - 1][j]);
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i][j - 1]);
			}
		}
		randomGridColours = GridGen::randomiseGridColours(3, 10);
		for (int i = 1; i < 3; i++)
		{
			ASSERT_NE(
				randomGridColours[i][0], randomGridColours[i - 1][0]);
		}
		for (int j = 1; j < 10; j++)
		{
			ASSERT_NE(
				randomGridColours[0][j], randomGridColours[0][j - 1]);
		}
		for (int i = 1; i < 3; i++) {
			for (int j = 1; j < 10; j++)
			{
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i - 1][j]);
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i][j - 1]);
			}
		}
	}

}