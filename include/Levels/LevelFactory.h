#pragma once
#include <map>
#include <string>
#include "Engine/TextureDict.h"

namespace Levels
{
	class LevelFactory
	{
	public:
		static void addTexture(const CellEntity& entity, CellGraphicsComponent& graphics);
	};
}