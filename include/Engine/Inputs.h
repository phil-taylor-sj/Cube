#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace Engine
{
	class Inputs
	{

	public:
		static Inputs* getInstance();

		void getInputs();

		void setWindow(std::shared_ptr<sf::RenderWindow> window);
		void setPlayerView(std::shared_ptr<sf::View> playerView);

	protected:
		Inputs() = default;

	private:
		static Inputs* _instance;

		std::shared_ptr<sf::RenderWindow> _window;
		std::shared_ptr<sf::View> _playerView;

		void _getKeyInputs();

		void _getResizeInputs(
			sf::Event& event
		);
	};
}