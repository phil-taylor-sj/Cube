#pragma once
#include <bitset>

namespace Actors
{
	struct ActorEntity
	{
		std::bitset<8> components;
		int id;
		bool isAssigned = false;
	};
}