#include "States/GameMode.h"

void GameMode::displayState(sf::RenderWindow& window,
							sf::View& playerView)
{
	playerView.setCenter(_player->getPosition());

	_currentLevel->displayGrid(window);
	_player->drawSprite(window);
}

void GameMode::updateState()
{
	_player->handleInput();
	_player->move(1.f);
}

GameMode::GameMode()
{
	_createLevel(5, 512.f);
	_createPlayer();
}

void GameMode::_createLevel(int widthOfCube, float commonCellWidth)
{
	_currentLevel = std::make_shared<Level>(widthOfCube, widthOfCube);
	_currentLevel->setCommonCellWidth(commonCellWidth);
	_currentLevel->constructCells();
}

void GameMode::_createPlayer()
{
	_player = std::make_shared<Player>();

	TextureDict::getInstance()->loadTexture("PlayerPlaceholder");
	_player->setTexture(
		TextureDict::getInstance()->getTexture("PlayerPlaceholder")
	);

	_player->setMovementSpeed(5.f);
	_player->setPosition(64.f * 2.5f, 64.f * 2.5f);
}