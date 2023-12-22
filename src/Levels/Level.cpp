#include "States/Level.h"

void Level::setCommonCellWidth(float commonCellWidth)
{
	_commonCellWidth = commonCellWidth;
}

void Level::constructCells()
{
	for (int i = 0; i < _xGridSize; i++)
	{
		for (int j = 0; j < _yGridSize; j++)
		{
			_grid[i][j] = std::make_shared<Void>();
		}
	}

	for (int i = 0; i < _xGridSize; i++)
	{
		_grid[i][0] = std::make_shared<Void>();
		_grid[i][_yGridSize - 1] = std::make_shared<Void>();
	}

	for (int j = 0; j < _yGridSize; j++)
	{
		_grid[0][j] = std::make_shared<Void>();
		_grid[_xGridSize - 1][j] = std::make_shared<Void>();
	}


	for (int i = 0; i < _xGridSize; i++)
	{
		for (int j = 0; j < _yGridSize; j++)
		{
			_grid[i][j]->setCellIndices(i, j);
			_grid[i][j]->setCellWidth(_commonCellWidth);
		}
	}

	std::vector<std::vector<std::string>> randomGridColours = 
		GridGen::randomiseGridColours(_xGridSize, _yGridSize);
	for (int i = 1; i < _xGridSize - 1; i++) 
	{
		for (int j = 1; j < _yGridSize - 1; j++)
		{
			_grid[i][j]->setTexture(
				TextureDict::getInstance()->getTexture(randomGridColours[i][j])
			);
			_grid[i][j]->updatePosition();
		}
	}

	sf::Texture& edgeTexture =
		TextureDict::getInstance()->getTexture("EdgeVoid");
	for (int i = 1; i < _xGridSize - 1; i++)
	{	
		// Configure northern edge cells 
		_grid[i][0]->setTexture(edgeTexture);
		_grid[i][0]->setRotation(180.f);
		_grid[i][0]->updatePosition();

		// Configure southern edge cells
		_grid[i][_yGridSize - 1]->setTexture(edgeTexture);
		_grid[i][_yGridSize - 1]->setRotation(0.f);
		_grid[i][_yGridSize - 1]->updatePosition();
	}

	for (int j = 1; j < _yGridSize - 1; j++)
	{
		// Configure western edge cells
		_grid[0][j]->setTexture(edgeTexture);
		_grid[0][j]->setRotation(90.f);
		_grid[0][j]->updatePosition();

		// Configure eastern edge cells
		_grid[_xGridSize - 1][j]->setTexture(edgeTexture);
		_grid[_xGridSize - 1][j]->setRotation(270.f);
		_grid[_xGridSize - 1][j]->updatePosition();
	}

	sf::Texture& cornerTexture = 
		TextureDict::getInstance()->getTexture("CornerVoid");
	
	// Configure North West Cell (type Void)
	_grid[0][0]->setTexture(cornerTexture);
	_grid[0][0]->setRotation(90.f);
	_grid[0][0]->updatePosition();

	// Configure North East Cell (type Void)
	_grid[_xGridSize - 1][0]->setTexture(cornerTexture);
	_grid[_xGridSize - 1][0]->setRotation(180.f);
	_grid[_xGridSize - 1][0]->updatePosition();
	
	// Configure South West Cell (type Void)
	_grid[0][_yGridSize - 1]->setTexture(cornerTexture);
	_grid[0][_yGridSize - 1]->setRotation(0.f);
	_grid[0][_yGridSize - 1]->updatePosition();

	// Configure South East Cell (type Void)
	_grid[_xGridSize - 1][_yGridSize - 1]->setTexture(cornerTexture);
	_grid[_xGridSize - 1][_yGridSize - 1]->setRotation(270.f);
	_grid[_xGridSize - 1][_yGridSize - 1]->updatePosition();
}

Level::Level(int xNumberOfRooms, int yNumberOfRooms)
{
	_xGridSize = std::max(xNumberOfRooms, 2) + 2;
	_yGridSize = std::max(yNumberOfRooms, 2) + 2;
	_commonCellWidth = 512.f;

	_grid.resize(_xGridSize);
	for (std::vector<std::shared_ptr<Cell>> &row : _grid)
	{
		row.resize(_yGridSize);
	}
	_loadAllTextures();
}

void Level::displayGrid(sf::RenderWindow& window)
{
	for (std::vector<std::shared_ptr<Cell>> &row : _grid) {
		for (std::shared_ptr<Cell> &cell : row) {
			cell->drawSprite(window);
		};
	};
};

void Level::_loadAllTextures()
{
	TextureDict::getInstance()->loadTexture("YellowRoom");
	TextureDict::getInstance()->loadTexture("WhiteRoom");
	TextureDict::getInstance()->loadTexture("GreenRoom");
	TextureDict::getInstance()->loadTexture("BlueRoom");
	TextureDict::getInstance()->loadTexture("RedRoom");

	TextureDict::getInstance()->loadTexture("CornerVoid");
	TextureDict::getInstance()->loadTexture("BridgeVoid");
	TextureDict::getInstance()->loadTexture("EdgeVoid");
};

//std::shared_ptr<Cell> testRoom = std::make_shared<Cell>();
//std::shared_ptr<Room> testCell = std::dynamic_pointer_cast<Room>(testCell);
//testCell = std::make_shared<Room>();
//std::shared_ptr<Room> testCell3 = std::dynamic_pointer_cast<Room>(testCell);

//std::dynamic_pointer_cast<Room>(_grid[0][0])->setTrapStatus(true);

//auto checkCellCast = std::dynamic_pointer_cast<Cell>(_grid[i][j]);
//auto checkRoomCast = std::dynamic_pointer_cast<Room>(_grid[i][j]);
//if (checkCellCast || checkRoomCast)
//{
//	_grid[i][j] = std::make_shared<Room>();
//	_grid[i][j] = std::dynamic_pointer_cast<Room>(_grid[i][j]);
//}

	//std::dynamic_pointer_cast<Room>(_grid[3][3])->setTrapStatus(true);

//std::shared_ptr<Void> firstCell =
//std::dynamic_pointer_cast<Void>(_grid[0][j]);
//std::shared_ptr<Void> lastCell =
//std::dynamic_pointer_cast<Void>(_grid[_xGridSize - 1][j]);

//
//std::shared_ptr<Void> firstCell =
//std::dynamic_pointer_cast<Void>(_grid[i][0]);
//std::shared_ptr<Void> lastCell =
//std::dynamic_pointer_cast<Void>(_grid[i][_yGridSize - 1]);