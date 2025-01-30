#include "../pch.h"
#include "Utilities/GridGen.h"

namespace GridGen_Tests
{ 
	class GridColoursTestsFixture : public ::testing::TestWithParam<std::tuple<int, int>>
	{
	protected:
		void SetUp() override
		{
			xSize = std::get<0>(GetParam());
			ySize = std::get<0>(GetParam());
		}			
		int xSize, ySize;
	};

	class GridColoursTestSize_F : public GridColoursTestsFixture {};
	TEST_P(GridColoursTestSize_F, CheckGridHasCorrectDimensions) 
	{
		std::vector<std::vector<std::string>> randomGridColours;

		randomGridColours = GridGen::randomiseGridColours(xSize, ySize);
		ASSERT_EQ(randomGridColours.size() , xSize);
		for (std::vector<std::string>& row : randomGridColours)
		{
			ASSERT_EQ(row.size(), ySize);
		}
	}

	INSTANTIATE_TEST_SUITE_P(
		CheckGridHasCorrectDimensions, GridColoursTestSize_F,
		::testing::Values(
			std::make_tuple<>(1, 1),
			std::make_tuple<>(4, 4),
			std::make_tuple<>(30, 30),
			std::make_tuple<>(10, 35)
		)
	);

	class GridColoursTestColours_F : public GridColoursTestsFixture {};
	TEST_P(GridColoursTestColours_F, CheckNoAdjacentColoursMatch
		)
	{
		std::vector<std::vector<std::string>> randomGridColours;

		randomGridColours = GridGen::randomiseGridColours(xSize, ySize);
		for (int i = 1; i < xSize; i++)
		{
			ASSERT_NE(
				randomGridColours[i][0], randomGridColours[i - 1][0]);
		}
		for (int j = 1; j < ySize; j++)
		{
			ASSERT_NE(
				randomGridColours[0][j], randomGridColours[0][j - 1]);
		}
		for (int i = 1; i < xSize; i++) {
			for (int j = 1; j < ySize; j++)
			{
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i - 1][j]);
				ASSERT_NE(
					randomGridColours[i][j], randomGridColours[i][j - 1]);
			}
		}
	}

	INSTANTIATE_TEST_SUITE_P(
		CheckNoAdjacentColoursMatch, GridColoursTestColours_F,
		::testing::Values(
			std::make_tuple<>(4, 4),
			std::make_tuple<>(30, 30),
			std::make_tuple<>(25, 30),
			std::make_tuple<>(3, 10)
		)
	);


}