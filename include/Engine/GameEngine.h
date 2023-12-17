#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine/Inputs.h"
#include "Engine/TextureDict.h"

enum GameState {
		TITLE_SCREEN,
		LEVEL_LOADING,
		LEVEL,
		PAUSED
};

class GameEngine
{
public:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Vector2f resolution;
	sf::VideoMode video;

	std::shared_ptr<sf::View> playerView;

	GameState currentGameState;

	void runEngine();
	
	GameEngine();
};