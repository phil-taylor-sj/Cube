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
		/**
		 * @brief Add sf:Texture instances to each cell's sprites based upon its type.
		 * @params cellTypes A vector array of CellTypeComponent instances.
		 * @params graphics A vector array of CellGraphicsComponent instances.
		 */
		static void addTextures(
			const std::vector<CellTypeComponent>& cellTypes,
			std::vector<CellGraphicsComponent>& graphics
		);

		static void addCollision(const std::vector<CellTypeComponent>& cellTypes, std::vector<CellCollisionComponent>& cellCollisions);
		static void updateCollision(
			const std::vector<CellTransformComponent>& cellTransforms,
			std::vector<CellCollisionComponent>& cellCollisions
		);
		static void assignCellTypes(const std::vector<std::vector<CellEntity>>& cellEntities, std::vector<CellTypeComponent>& cellTypes);
		static void loadAllLevelTextures();
	
	private:
		static const std::map<CellSubtypes, std::string> m_colourFilenames;
		static const std::map<CellTypes, std::string> m_voidFilenames;
	};
}