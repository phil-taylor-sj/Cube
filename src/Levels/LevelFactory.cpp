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
		int xGridSize = cellEntities.size();
		int yGridSize = cellEntities[0].size();

		std::vector<std::vector<std::string>> randomGridColours =
			GridGen::randomiseGridColours(xGridSize, yGridSize);
		for (int i = 1; i < xGridSize - 1; i++)
		{
			for (int j = 1; j < yGridSize - 1; j++)
			{
				int cellId = cellEntities[i][j].cellId;
				cellTypes[cellId].type = "Room";
				cellTypes[cellId].subtype = randomGridColours[i][j];
			}
		}

		for (int i = 0; i < yGridSize; i++)
		{
			CellTypeComponent& typeLeft = cellTypes[cellEntities[0][i].cellId];
			CellTypeComponent& typeRight = cellTypes[cellEntities[xGridSize - 1][i].cellId];
			typeLeft.type = "EdgeVoid";
			typeLeft.subtype = "Left";
			typeRight.type = "EdgeVoid";
			typeRight.subtype =  "Right";
		}

		for (int i = 0; i < xGridSize; i++)
		{
			CellTypeComponent& typeUpper = cellTypes[cellEntities[i][0].cellId];
			CellTypeComponent& typeLower = cellTypes[cellEntities[yGridSize - 1][i].cellId];
			typeUpper.type = "EdgeVoid";
			typeUpper.subtype = "Left";
			typeLower.type = "EdgeVoid";
			typeLower.subtype = "Right";
		}

		CellTypeComponent& upperLeft = cellTypes[cellEntities[0][0].cellId];
		upperLeft.type = "CornerVoid";
		upperLeft.subtype = "UpperLeft";

		CellTypeComponent& upperRight = cellTypes[cellEntities[xGridSize - 1][0].cellId];
		upperRight.type = "CornerVoid";
		upperRight.subtype = "UpperRight";

		CellTypeComponent& lowerLeft = cellTypes[cellEntities[0][yGridSize - 1].cellId];
		lowerLeft.type = "CornerVoid";
		lowerLeft.subtype = "LowerLeft";

		CellTypeComponent& lowerRight = cellTypes[cellEntities[xGridSize - 1][yGridSize - 1].cellId];
		lowerRight.type = "CornerVoid";
		lowerRight.subtype = "LowerRight";
	}

	void LevelFactory::addTextures(const std::vector<CellTypeComponent>& cellTypes, std::vector<CellGraphicsComponent>& graphics)
	{
		std::map<std::string, float> voidConfig;
		voidConfig.insert({ "UpperEdge", 180.f });
		voidConfig.insert({ "LowerEdge", 0.f });
		voidConfig.insert({ "LeftEdge", 90.f });
		voidConfig.insert({ "RightEdge", 270.f });
		voidConfig.insert({ "UpperLeft", 90.f });
		voidConfig.insert({ "UpperRight", 180.f });
		voidConfig.insert({ "LowerLeft", 0.f });
		voidConfig.insert({ "LowerRight", 270.f });


		for (int i = 0; i < cellTypes.size(); i++)
		{
			if (cellTypes[i].type == "Room")
			{
				graphics[i].sprite.setTexture(
					Assets::TextureDict::getInstance()->getTexture(cellTypes[i].subtype)
				);
			}

			if (voidConfig.count(cellTypes[i].subtype) > 0)
			{
				graphics[i].sprite.setTexture(
					Assets::TextureDict::getInstance()->getTexture(cellTypes[i].type)
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

	void LevelFactory::addCollision(const std::vector<CellTypeComponent>& cellTypes, std::vector<CellCollisionComponent>& cellCollisions)
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
}