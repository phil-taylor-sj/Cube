#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine/GameEngine.h"



namespace Engine
{

	class GameEngine;
	
	class Inputs
	{
	public:
		void getInputs(GameEngine& engine);
		void setWindow(std::shared_ptr<sf::RenderWindow> window);
		void setPlayerView(std::shared_ptr<sf::View> playerView);

		Inputs();

	private:

		std::shared_ptr<sf::RenderWindow> m_window;
		std::shared_ptr<sf::View> m_playerView;

		void m_getResizeInputs(
			sf::Event& event
		);
	};
}