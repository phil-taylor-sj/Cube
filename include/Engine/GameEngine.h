#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine/Inputs.h"
#include "Assets/TextureDict.h"
#include "Scenes/GameScene.h"

namespace Engine
{
	class GameEngine
	{
	public:
		std::shared_ptr<sf::RenderWindow> window;
		sf::Vector2f resolution;
		sf::VideoMode video;

		std::shared_ptr<sf::View> playerView;

		void runEngine();

		GameEngine();

	private:
		std::unique_ptr<Scenes::Scene> m_currentScene;

	};
}