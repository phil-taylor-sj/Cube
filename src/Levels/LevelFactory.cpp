#include "Levels/LevelFactory.h"

namespace Levels
{
	void LevelFactory::loadAllLevelTextures()
	{
		std::string textureNames[8] = {
			"YellowRoom",
			"WhiteRoom",
			"GreenRoom",
			"BlueRoom",
			"RedRoom",
			"CornerVoid",
			"BridgeVoid",
			"EdgeVoid"
		};

		for (std::string name : textureNames)
		{
			Assets::TextureDict::getInstance()->loadTexture(name);
		}
	};

	void LevelFactory::assignCellTypes(const std::vector<std::vector<CellEntity>>& cellEntities, std::vector<CellTypeComponent>& cellTypes)
	{
		std::map<std::string, CellSubtypes> colours {
			{"Yellow", CellSubtypes::YELLOW},
			{"White", CellSubtypes::WHITE},
			{"Green", CellSubtypes::GREEN},
			{"Blue", CellSubtypes::BLUE},
			{"Red", CellSubtypes::RED}
		};

		int xGridSize = cellEntities.size();
		int yGridSize = cellEntities[0].size();

		std::vector<std::vector<std::string>> randomGridColours =
			GridGen::randomiseGridColours(xGridSize, yGridSize);
		for (int i = 1; i < xGridSize - 1; i++)
		{
			for (int j = 1; j < yGridSize - 1; j++)
			{
				int cellId = cellEntities[i][j].cellId;
				cellTypes[cellId].type = CellTypes::ROOM;
				cellTypes[cellId].subtype = colours[randomGridColours[i][j]];
			}
		}

		for (int i = 0; i < yGridSize; i++)
		{
			CellTypeComponent& typeLeft = cellTypes[cellEntities[0][i].cellId];
			CellTypeComponent& typeRight = cellTypes[cellEntities[xGridSize - 1][i].cellId];
			typeLeft.type = CellTypes::EDGE_VOID;
			typeLeft.subtype = CellSubtypes::LEFT_EDGE;
			typeRight.type = CellTypes::EDGE_VOID;
			typeRight.subtype =  CellSubtypes::RIGHT_EDGE;
		}

		for (int i = 0; i < xGridSize; i++)
		{
			CellTypeComponent& typeUpper = cellTypes[cellEntities[i][0].cellId];
			CellTypeComponent& typeLower = cellTypes[cellEntities[i][yGridSize - 1].cellId];
			typeUpper.type = CellTypes::EDGE_VOID;
			typeUpper.subtype = CellSubtypes::UPPER_EDGE;
			typeLower.type = CellTypes::EDGE_VOID;
			typeLower.subtype = CellSubtypes::LOWER_EDGE;
		}

		CellTypeComponent& upperLeft = cellTypes[cellEntities[0][0].cellId];
		upperLeft.type = CellTypes::CORNER_VOID;
		upperLeft.subtype = CellSubtypes::UPPER_LEFT;

		CellTypeComponent& upperRight = cellTypes[cellEntities[xGridSize - 1][0].cellId];
		upperRight.type = CellTypes::CORNER_VOID;
		upperRight.subtype = CellSubtypes::UPPER_RIGHT;

		CellTypeComponent& lowerLeft = cellTypes[cellEntities[0][yGridSize - 1].cellId];
		lowerLeft.type = CellTypes::CORNER_VOID;
		lowerLeft.subtype = CellSubtypes::LOWER_LEFT;

		CellTypeComponent& lowerRight = cellTypes[cellEntities[xGridSize - 1][yGridSize - 1].cellId];
		lowerRight.type = CellTypes::CORNER_VOID;
		lowerRight.subtype = CellSubtypes::LOWER_RIGHT;
	}

	void LevelFactory::addTextures(const std::vector<CellTypeComponent>& cellTypes, std::vector<CellGraphicsComponent>& graphics)
	{
		std::map<CellSubtypes, float> voidConfig {
			{CellSubtypes::UPPER_EDGE, 180.f},
			{CellSubtypes::LOWER_EDGE, 0.f},
			{CellSubtypes::LEFT_EDGE, 90.f},
			{CellSubtypes::RIGHT_EDGE, 270.f},
			{CellSubtypes::UPPER_LEFT, 90.f},
			{CellSubtypes::UPPER_RIGHT, 180.f},
			{CellSubtypes::LOWER_LEFT, 0.f},
			{CellSubtypes::LOWER_RIGHT, 270.f}
		};

		for (int i = 0; i < cellTypes.size(); i++)
		{
			if (cellTypes[i].type == CellTypes::ROOM)
			{
				graphics[i].sprite.setTexture(
					Assets::TextureDict::getInstance()->getTexture(
						m_colourFilenames.at(cellTypes[i].subtype)
					)
				);
			}

			if (voidConfig.count(cellTypes[i].subtype) > 0)
			{
				graphics[i].sprite.setTexture(
					Assets::TextureDict::getInstance()->getTexture(
						m_voidFilenames.at(cellTypes[i].type)
					)
				);
			}

			graphics[i].sprite.setOrigin(
				graphics[i].sprite.getLocalBounds().width * 0.5f,
				graphics[i].sprite.getLocalBounds().height * 0.5f
			);

			if (voidConfig.count(cellTypes[i].subtype) > 0)
			{
				graphics[i].textureRotation = voidConfig.find(cellTypes[i].subtype)->second;
				graphics[i].sprite.setRotation(graphics[i].textureRotation);

			}
		}
	}

	void LevelFactory::addCollision(
		const std::vector<CellTypeComponent>& cellTypes, 
		std::vector<CellCollisionComponent>& cellCollisions
	)
	{


		// Initialise the eight outer walls
		float wallLength = 0.34375;
		float wallDepth = 0.078125;
		float wallHalfLength = 0.5f * wallLength;
		float wallHalfDepth = 0.5f * wallDepth;

		float wallPositions[8][2] = {
			{wallHalfDepth,  wallHalfLength},
			{wallHalfDepth, 1.f - wallHalfLength},
			{1.f - wallHalfDepth, wallHalfLength},
			{1.f - wallHalfDepth, 1.f - wallHalfLength},
			{wallHalfLength,  wallHalfDepth},
			{wallHalfLength, 1.f - wallHalfDepth},
			{1.f - wallHalfLength, wallHalfDepth},
			{1.f - wallHalfLength, 1.f - wallHalfDepth}
		};

		for (int i = 0; i <= 7; i++)
		{
			wallPositions[i][0] -= 0.5F;
			wallPositions[i][1] -= 0.5f;
		}

		for (CellCollisionComponent& collision : cellCollisions)
		{
			collision.relativeBroadRadius = 1.5f;

			for (int i = 0; i <= 3; i++)
			{
				collision.staticWalls[i].setRelativeDimensions(wallDepth, wallLength);
				collision.staticWalls[i].setRelativePosition(
					wallPositions[i][0], wallPositions[i][1]
				);
			}

			for (int i = 4; i <= 7; i++)
			{
				collision.staticWalls[i].setRelativeDimensions(wallLength, wallDepth);
				collision.staticWalls[i].setRelativePosition(
					wallPositions[i][0], wallPositions[i][1]
				);
			}
		}
	}

	void LevelFactory::updateCollision(
		const std::vector<CellTransformComponent>& cellTransforms,
		std::vector<CellCollisionComponent>& cellCollisions)
	{
		for (int i = 0; i < cellCollisions.size(); i++)
		{
			cellCollisions[i].broadCircle.setPosition(cellTransforms[i].position);
			cellCollisions[i].broadCircle.setRadius(
				cellCollisions[i].relativeBroadRadius *
				cellTransforms[i].cellWidth
			);
			for (CellStaticWall& wall : cellCollisions[i].staticWalls)
			{
				wall.setCellPosition(cellTransforms[i].position);
				wall.setCellWidth(cellTransforms[i].cellWidth);
			}
		}
	}

	const std::map<CellSubtypes, std::string> LevelFactory::m_colourFilenames = {
		{CellSubtypes::YELLOW, "YellowRoom"},
		{CellSubtypes::WHITE, "WhiteRoom"},
		{CellSubtypes::GREEN, "GreenRoom"},
		{CellSubtypes::BLUE, "BlueRoom"},
		{CellSubtypes::RED, "RedRoom"}
	};

	const std::map<CellTypes, std::string> LevelFactory::m_voidFilenames = {
		{CellTypes::CORNER_VOID, "CornerVoid"},
		{CellTypes::EDGE_VOID, "EdgeVoid"},
		{CellTypes::BRIDGE_VOID, "BridgeVoid"}
	};

}