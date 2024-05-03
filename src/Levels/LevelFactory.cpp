#include "Levels/LevelFactory.h"

namespace Levels
{

	void LevelFactory::setActiveComponentTypes(
		const std::vector<CellTypeComponent>& cellTypes, 
		std::vector<CellEntity>& entities) 
	{
		for (int i = 0; i < cellTypes.size(); i++)
		{

			auto& activeTypes = entities[i].components; //bitset
			activeTypes.set(CellComponentTypes::TYPE);
			activeTypes.set(CellComponentTypes::GRAPHICS);
			activeTypes.set(CellComponentTypes::COLLISION);
			activeTypes.set(CellComponentTypes::TRANSFORM);
			activeTypes.set(CellComponentTypes::MOVE);
			if (cellTypes[i].type == CellTypes::ROOM)
			{
				activeTypes.set(CellComponentTypes::NUMBERS);
				activeTypes.set(CellComponentTypes::MOVE);
			}

		}
	}

	void LevelFactory::loadAllLevelTextures()
	{
		std::string textureNames[9] = {
			"YellowRoom",
			"WhiteRoom",
			"GreenRoom",
			"BlueRoom",
			"RedRoom",
			"CornerVoid",
			"BridgeVoid",
			"EdgeVoid",
			"BackgroundVoid"
		};

		for (std::string name : textureNames)
		{
			Assets::TextureDict::getInstance()->loadTexture(name);
			if (name == "BackgroundVoid")
			{
				Assets::TextureDict::getInstance()->setRepeated(name, true);
			}
		}
	};

	void LevelFactory::createBackground(
		sf::Sprite& backgroundSprite, float xGridSize, float yGridSize)
	{
		sf::Texture& texture = Assets::TextureDict::getInstance()->getTexture("BackgroundVoid");
		backgroundSprite.setTexture(texture);
		backgroundSprite.setTextureRect(
			sf::IntRect(0, 0, 
				backgroundSprite.getTextureRect().width * xGridSize, 
				backgroundSprite.getTextureRect().height * yGridSize)
			);
	}

	void LevelFactory::assignCellTypes(const std::vector<std::vector<int>>& cellEntityGrid, std::vector<CellTypeComponent>& cellTypes)
	{
		std::map<std::string, CellColours> colours {
			{"Yellow", CellColours::YELLOW},
			{"White", CellColours::WHITE},
			{"Green", CellColours::GREEN},
			{"Blue", CellColours::BLUE},
			{"Red", CellColours::RED}
		};

		int xGridSize = cellEntityGrid.size();
		int yGridSize = cellEntityGrid[0].size();

		std::vector<std::vector<std::string>> randomGridColours =
			GridGen::randomiseGridColours(xGridSize, yGridSize);
		for (int i = 1; i < xGridSize - 1; i++)
		{
			for (int j = 1; j < yGridSize - 1; j++)
			{
				int cellId = cellEntityGrid[i][j];
				cellTypes[cellId].type = CellTypes::ROOM;
				cellTypes[cellId].colour = colours[randomGridColours[i][j]];
			}
		}

		for (int i = 0; i < yGridSize; i++)
		{
			CellTypeComponent& typeLeft = cellTypes[cellEntityGrid[0][i]];
			CellTypeComponent& typeRight = cellTypes[cellEntityGrid[xGridSize - 1][i]];
			typeLeft.type = CellTypes::EDGE_VOID;
			typeLeft.subtype = CellSubtypes::LEFT_EDGE;
			typeRight.type = CellTypes::EDGE_VOID;
			typeRight.subtype =  CellSubtypes::RIGHT_EDGE;
		}

		for (int i = 0; i < xGridSize; i++)
		{
			CellTypeComponent& typeUpper = cellTypes[cellEntityGrid[i][0]];
			CellTypeComponent& typeLower = cellTypes[cellEntityGrid[i][yGridSize - 1]];
			typeUpper.type = CellTypes::EDGE_VOID;
			typeUpper.subtype = CellSubtypes::UPPER_EDGE;
			typeLower.type = CellTypes::EDGE_VOID;
			typeLower.subtype = CellSubtypes::LOWER_EDGE;
		}

		CellTypeComponent& upperLeft = cellTypes[cellEntityGrid[0][0]];
		upperLeft.type = CellTypes::CORNER_VOID;
		upperLeft.subtype = CellSubtypes::UPPER_LEFT;

		CellTypeComponent& upperRight = cellTypes[cellEntityGrid[xGridSize - 1][0]];
		upperRight.type = CellTypes::CORNER_VOID;
		upperRight.subtype = CellSubtypes::UPPER_RIGHT;

		CellTypeComponent& lowerLeft = cellTypes[cellEntityGrid[0][yGridSize - 1]];
		lowerLeft.type = CellTypes::CORNER_VOID;
		lowerLeft.subtype = CellSubtypes::LOWER_LEFT;

		CellTypeComponent& lowerRight = cellTypes[cellEntityGrid[xGridSize - 1][yGridSize - 1]];
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
						m_colourFilenames.at(cellTypes[i].colour)
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

	void LevelFactory::addCollisions(
		const std::vector<CellTypeComponent>& cellTypes, 
		std::vector<CellCollisionComponent>& cellCollisions
	)
	{
		for (CellCollisionComponent& collision : cellCollisions)
		{
			m_addWallCollisions(collision);
		}

		for (int i = 0; i < cellCollisions.size(); i++)
		{
			m_addFloorCollisions(cellTypes[i], cellCollisions[i]);
		}
	}

	void LevelFactory::m_addWallCollisions(CellCollisionComponent& collision)
	{
		float wallLength = 0.34375;
		float wallDepth = 0.078125;
		float wallHalfLength = 0.5f * wallLength;
		float wallHalfDepth = 0.5f * wallDepth;

		// Initialise the eight outer walls
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

	void LevelFactory::m_addFloorCollisions(
		const CellTypeComponent& type,
		CellCollisionComponent& collision)
	{
		if (type.type == CellTypes::ROOM)
		{
			CellStaticRectangle roomFloor = CellStaticRectangle();
			roomFloor.setRelativeDimensions(1.f, 1.f);
			roomFloor.setRelativePosition(0.f, 0.f);
			collision.staticFloors.push_back(roomFloor);
		}

		if (type.type == CellTypes::EDGE_VOID || type.type == CellTypes::BRIDGE_VOID)
		{
			float floorDepth = 0.078125;
			float floorLength = 0.4;
			float floorHalfLength = 0.5f * floorLength;
			float floorHalfDepth = 0.5f * floorDepth;
			
			auto setUpperTunnelFloor = 
				[floorDepth, floorLength, floorHalfLength, floorHalfDepth]
				(CellCollisionComponent& collision)
			{	
				CellStaticRectangle newFloor = CellStaticRectangle();
				newFloor.setRelativeDimensions(floorLength, floorDepth);
				newFloor.setRelativePosition(0.f, floorHalfDepth);
				collision.staticFloors.push_back(newFloor);
			};

			auto setLowerTunnelFloor =
				[floorDepth, floorLength, floorHalfLength, floorHalfDepth]
				(CellCollisionComponent& collision)
				{
					CellStaticRectangle newFloor = CellStaticRectangle();
					newFloor.setRelativeDimensions(floorLength, floorDepth);
					newFloor.setRelativePosition(0.f, 0.5f - floorHalfDepth);
					collision.staticFloors.push_back(newFloor);
				};

			auto setRightTunnelFloor =
				[floorDepth, floorLength, floorHalfLength, floorHalfDepth]
				(CellCollisionComponent& collision)
				{
					CellStaticRectangle newFloor = CellStaticRectangle();
					newFloor.setRelativeDimensions(floorDepth, floorLength);
					newFloor.setRelativePosition(0.5f - floorHalfDepth, 0.f);
					collision.staticFloors.push_back(newFloor);
				};

			auto setLeftTunnelFloor =
				[floorDepth, floorLength, floorHalfLength, floorHalfDepth]
				(CellCollisionComponent& collision)
				{
					CellStaticRectangle newFloor = CellStaticRectangle();
					newFloor.setRelativeDimensions(floorDepth, floorLength);
					newFloor.setRelativePosition(floorHalfDepth, 0.f);
					collision.staticFloors.push_back(newFloor);
				};

			switch (type.subtype)
			{
			case CellSubtypes::UPPER_EDGE:
				setLowerTunnelFloor(collision);
				break;
			case CellSubtypes::LOWER_EDGE:
				setUpperTunnelFloor(collision);
				break;
			case CellSubtypes::LEFT_EDGE:
				setRightTunnelFloor(collision);
				break;
			case CellSubtypes::RIGHT_EDGE:
				setLeftTunnelFloor(collision);
				break;
			case CellSubtypes::BRIDGE_UPPER_LEFT:
				setLowerTunnelFloor(collision);
				setRightTunnelFloor(collision);
				break;
			case CellSubtypes::BRIDGE_UPPER_RIGHT:
				setLowerTunnelFloor(collision);
				setLeftTunnelFloor(collision);
				break;
			case CellSubtypes::BRIDGE_LOWER_LEFT:
				setUpperTunnelFloor(collision);
				setRightTunnelFloor(collision);
				break;
			case CellSubtypes::BRIDGE_LOWER_RIGHT:
				setUpperTunnelFloor(collision);
				setLeftTunnelFloor(collision);
				break;
			case CellSubtypes::BRIDGE_LEFT_UPPER:
				setRightTunnelFloor(collision);
				setLowerTunnelFloor(collision);				
				break;
			case CellSubtypes::BRIDGE_LEFT_LOWER:
				setRightTunnelFloor(collision);
				setUpperTunnelFloor(collision);				
				break;
			case CellSubtypes::BRIDGE_RIGHT_UPPER:
				setLeftTunnelFloor(collision);
				setLowerTunnelFloor(collision);
				break;
			case CellSubtypes::BRIDGE_RIGHT_LOWER:
				setLeftTunnelFloor(collision);
				setUpperTunnelFloor(collision);				
				break;
			default:
				break;
			}
		}
	}

	void LevelFactory::updateCollisions(
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
			for (CellStaticRectangle& wall : cellCollisions[i].staticWalls)
			{
				wall.setCellPosition(cellTransforms[i].position);
				wall.setCellWidth(cellTransforms[i].cellWidth);
			}
			for (CellStaticRectangle& floor : cellCollisions[i].staticFloors)
			{
				floor.setCellPosition(cellTransforms[i].position);
				floor.setCellWidth(cellTransforms[i].cellWidth);
			}
		}
	}

	void LevelFactory::addNumbers(
		const CellTransformComponent& cellTransform, 
		CellNumbersComponent& cellNumbers)
	{
		sf::Text& text = cellNumbers.text;
		text.setFont(Assets::FontDict::getInstance()->getFont("Tuffy"));
		text.setCharacterSize(48);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
		sf::FloatRect shape = text.getLocalBounds();
		text.setOrigin(0.5 * shape.width, 0.5f * shape.height);
		
	}

	const std::map<CellColours, std::string> LevelFactory::m_colourFilenames = {
		{CellColours::YELLOW, "YellowRoom"},
		{CellColours::WHITE, "WhiteRoom"},
		{CellColours::GREEN, "GreenRoom"},
		{CellColours::BLUE, "BlueRoom"},
		{CellColours::RED, "RedRoom"}
	};

	const std::map<CellTypes, std::string> LevelFactory::m_voidFilenames = {
		{CellTypes::CORNER_VOID, "CornerVoid"},
		{CellTypes::EDGE_VOID, "EdgeVoid"},
		{CellTypes::BRIDGE_VOID, "BridgeVoid"}
	};

}