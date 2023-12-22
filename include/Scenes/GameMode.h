#pragma once
#include <SFML/Graphics.hpp>
#include "Assets/Player.h"
#include "States/Level.h"
#include "Scenes/BaseScene.h"
#include "Engine/TextureDict.h"



class GameScene : public BaseScene
{
public:
	void updateScene() override;
	void displayScene(sf::RenderWindow& window,
					sf::View& playerVide) override;
	GameScene();

private:
	std::shared_ptr<Level> _currentLevel;
	std::shared_ptr<Player> _player;
	void _createLevel(int mazeWidth, float cellWidth);
	void _createPlayer();

};
