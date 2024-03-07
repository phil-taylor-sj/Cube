#pragma once
#include <bitset>
#include <string>

namespace Levels
{
	struct CellEntity
	{
		std::bitset<8> components;
		int cellId;
	};
}