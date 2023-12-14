#include "Engine/Inputs.h"

void Inputs::getInputs()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed
			|| event.type == sf::Event::KeyReleased)
		{
			_getKeyInputs();
		}

		if (event.type == sf::Event::Resized)
		{
			_getResizeInputs(event);
		}
	}
}

void Inputs::setWindow(std::shared_ptr<sf::RenderWindow> window)
{
	_window = window;
}

void Inputs::setPlayerView(std::shared_ptr<sf::View> playerView)
{
	_playerView = playerView;
}

void Inputs::setPlayer(std::shared_ptr<Player> player)
{
	_player = player;
}

Inputs* Inputs::_instance = nullptr;

Inputs* Inputs::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Inputs;
	}
		return _instance;
}

void Inputs::_getKeyInputs()
{
	_player->setUpMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)
	);
	_player->setDownMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)
	);
	_player->setLeftMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	);
	_player->setRightMovement(
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)
	);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		_window->close();
	}
};

void Inputs::_getResizeInputs(
	sf::Event & event
)
{
	_playerView->setSize(
		event.size.width,
		event.size.height
	);
}