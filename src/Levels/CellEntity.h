#pragma once
#include <bitset>
#include <string>

namespace Levels
{
	struct CellEntity
	{
		std::bitset<12> components;
		int cellId;
	};
}