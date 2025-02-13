#pragma once
#include <map>
#include <string>
#include "math.h"
#include "Assets/TextureDict.h"
#include "Levels/CellEntity.h"
#include "Levels/CellComponents.h"
#include "Utilities/GridGen.h"
#include "Levels/CellTypes.h"
#include "Assets/FontDict.h"
#include "Actors/ActorConfig.h"

namespace Levels
{
	class LevelFactory
	{
	public:

		static void setActiveComponentTypes(
			const std::vector<CellTypeComponent>& cellTypes,
			std::vector<CellEntity>& entities
		);

		/**
		 * @brief Add sf:Texture instances to each cell's sprites based upon its type.
		 * @params cellTypes A vector array of CellTypeComponent instances.
		 * @params graphics A vector array of CellGraphicsComponent instances.
		 */
		static void addTextures(
			const std::vector<CellTypeComponent>& cellTypes,
			std::vector<CellGraphicsComponent>& graphics
		);

		static void createBackground(
			sf::Sprite& backgroundSprite, float xGridSize, float yGridSize);

		static void addCollisions(const std::vector<CellTypeComponent>& cellTypes, std::vector<CellCollisionComponent>& cellCollisions);
		
		static void assignCellTypes(const std::vector<std::vector<int>>& cellEntityGrid, std::vector<CellTypeComponent>& cellTypes);
		static void loadAllLevelTextures();
	
		static void addNumbers(const CellTransformComponent& cellTransform, CellNumbersComponent& cellNumbers);

		

	private:
		static void m_addWallCollisions(CellCollisionComponent& collision);
		static void m_addFloorCollisions(const CellTypeComponent& type, CellCollisionComponent& collision);
		static void m_addSensorCollisions(CellCollisionComponent& collision);

		static const std::map<CellColours, std::string> m_colourFilenames;
		static const std::map<CellTypes, std::string> m_voidFilenames;
	};
}