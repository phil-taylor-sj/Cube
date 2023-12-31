#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <typeinfo>
#include "Engine/Inputs.h"
#include "Assets/TextureDict.h"
#include "Scenes/GameScene.h"
#include "Engine/GameEngine.h"
#include "Engine/Action.h"

namespace Engine
{
	class GameEngine
	{
	public:
		std::shared_ptr<sf::RenderWindow> window;
		sf::Vector2f resolution;
		sf::VideoMode video;

		std::shared_ptr<sf::View> playerView;


		void checkInput(sf::Keyboard::Key key, sf::Event::EventType eventType);

		void runEngine();

		GameEngine();

	private:
		std::unique_ptr<Scenes::Scene<Scenes::GameSceneActionNames>> m_currentScene;

	};
}