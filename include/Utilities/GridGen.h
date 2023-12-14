#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>

namespace GridGen
{

	std::vector<std::vector<std::string>> randomiseGridColours(
		int totalCellX, int totalCellsY
	);


}