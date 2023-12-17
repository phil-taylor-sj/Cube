#pragma once
#include <SFML/Graphics.hpp>
#include "Assets/Player.h"
#include "States/Level.h"
#include "States/BaseState.h"
#include "Engine/TextureDict.h"



class GameMode : public BaseState
{
public:
	void updateState() override;
	void displayState(sf::RenderWindow& window,
					sf::View& playerVide) override;
	GameMode();

private:
	std::shared_ptr<Level> _currentLevel;
	std::shared_ptr<Player> _player;
	void _createLevel(int mazeWidth, float cellWidth);
	void _createPlayer();

};
