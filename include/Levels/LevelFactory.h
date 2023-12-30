#pragma once
#include <map>
#include <string>
#include "math.h"
#include "Assets/TextureDict.h"
#include "Levels/CellEntity.h"
#include "Levels/CellComponents.h"
#include "Utilities/GridGen.h"

namespace Levels
{
	class LevelFactory
	{
	public:
		static void addTextures(
			const std::vector<CellTypeComponent>& cellTypes,
			std::vector<CellGraphicsComponent>& graphics
		);
		static void addCollision(const std::vector<CellTypeComponent>& cellTypes, std::vector<CellCollisionComponent>& cellCollisions);
		static void assignCellTypes(const std::vector<std::vector<CellEntity>>& cellEntities, std::vector<CellTypeComponent>& cellTypes);
		static void loadAllLevelTextures();
	
	};
}