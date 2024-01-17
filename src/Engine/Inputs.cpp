#include "Engine/Inputs.h"

namespace Engine
{
	void Inputs::getInputs(GameEngine& engine)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed
				|| event.type == sf::Event::KeyReleased)
			{
				engine.checkInput(event.key.code, event.type);
			}

			if (event.type == sf::Event::Resized)
			{
				m_getResizeInputs(event);
			}
		}

		engine.sendCursorPosition(
			sf::Mouse::getPosition(*m_window).x,
			sf::Mouse::getPosition(*m_window).y
		);
	}

	void Inputs::setWindow(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
	}

	void Inputs::setPlayerView(std::shared_ptr<sf::View> playerView)
	{
		m_playerView = playerView;
	}

	Inputs::Inputs()
	{

	}

	void Inputs::m_getResizeInputs(
		sf::Event& event
	)
	{
		m_playerView->setSize(
			event.size.width,
			event.size.height
		);
	}
}