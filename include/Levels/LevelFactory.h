#pragma once
#include <map>
#include <string>
#include "math.h"
#include "Assets/TextureDict.h"
#include "Levels/CellEntity.h"
#include "Levels/CellComponents.h"
#include "Utilities/GridGen.h"
#include "Levels/CellTypes.h"

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
	
	private:
		static const std::map<CellSubtypes, std::string> m_colourFilenames;
		static const std::map<CellTypes, std::string> m_voidFilenames;
	};
}