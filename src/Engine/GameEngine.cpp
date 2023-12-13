#include "Engine/GameEngine.h"

void GameEngine::runEngine()
{
	sf::Vector2f resolution = sf::Vector2f(1000.0, 750.0);
	sf::VideoMode video(resolution.x, resolution.y);
	
	std::shared_ptr<sf::RenderWindow> window = 
		std::make_shared<sf::RenderWindow>(video, "Cube");

	Level newLevel = Level(5, 5);
	newLevel.setCommonCellWidth(1024.f);

	std::shared_ptr<Player> player = std::make_shared<Player>();
	
	TextureDict::getInstance()->loadTexture("PlayerPlaceholder");
	player->setTexture(
		TextureDict::getInstance()->getTexture("PlayerPlaceholder")
	);
	player->setMovementSpeed(5.0);
	player->setPosition(512.f * 2.5f, 512.f * 2.5f);
	
	newLevel.constructCells();

	std::shared_ptr<sf::View> playerView = 
		std::make_shared<sf::View> (
		sf::Vector2f(0.5*resolution.x, 0.5*resolution.y),
		sf::Vector2f(resolution.x, resolution.y)
	);
	playerView->setViewport(sf::FloatRect(-0.f, -0.f, 1.f, 1.f));

	window->setFramerateLimit(60);
	
	Inputs::getInstance()->setWindow(window);
	Inputs::getInstance()->setPlayerView(playerView);
	Inputs::getInstance()->setPlayer(player);

	while (window->isOpen())
	{
		window->clear();
		Inputs::getInstance()->getInputs();
		player->move(1.0);
		playerView->setCenter(player->getPosition());
		window->setView(*playerView);
		newLevel.displayGrid(*window);
		player->drawSprite(*window);
		window->display();
	}
}

GameEngine::GameEngine()
{

}