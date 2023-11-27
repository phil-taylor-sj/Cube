#include "GridGen.h"


std::vector<std::vector<std::string>> GridGen::randomiseGridColours(
	int totalCellsX, int totalCellsY
)
{
	int totalColours = 5;
	std::string randomColour;
	std::array<std::string, 5> colourList {
		"BlueRoom", "RedRoom", "GreenRoom", "YellowRoom", "WhiteRoom"
	};

	std::vector<std::vector<std::string>> randomGridColours;
	randomGridColours.resize(totalCellsX);
	for (std::vector<std::string>& row : randomGridColours)
	{
		row.resize(totalCellsY);
	}

	srand(time(NULL));
	for (int i = 1; i < totalCellsX; i++)
	{
		randomColour = colourList[rand() % totalColours];
		while (randomColour == randomGridColours[i-1][0])
		{
			randomColour = colourList[rand() % totalColours];
		}
		randomGridColours[i][0] = randomColour;
		
	}
	for (int j = 1; j < totalCellsY; j++)
	{
		randomColour = colourList[rand() % totalColours];
		while (randomColour == randomGridColours[0][j-1])
		{
			randomColour = colourList[rand() % totalColours];
		}	
		randomGridColours[0][j] = randomColour;
	}
	for (int i = 1; i < totalCellsX; i++) {
		for (int j = 1; j < totalCellsY; j++)
		{
			randomColour = colourList[rand() % totalColours];
			while (randomColour == randomGridColours[i][j-1]
				|| randomColour == randomGridColours[i-1][j])
			{
				randomColour = colourList[rand() % totalColours];
			}
			randomGridColours[i][j] = randomColour;
		}
	}
	return randomGridColours;
}
