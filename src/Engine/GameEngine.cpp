#include "Engine/GameEngine.h"
#include "States/GameMode.h"

void GameEngine::runEngine()
{

	Inputs::getInstance()->setWindow(window);
	Inputs::getInstance()->setPlayerView(playerView);


	bool isPaused = false;

	GameMode newGame = GameMode();

	while (window->isOpen())
	{
		Inputs::getInstance()->getInputs(isPaused);

		newGame.updateState();
		window->clear();
		//switch(currentGameState) {
		//	case TITLE_SCREEN:
		//		break;
		//	case LEVEL:
		//		break;
		//	default:
		//}

		newGame.displayState(*window, *playerView);
		window->setView(*playerView);
		window->display();
	}
}

GameEngine::GameEngine()
{
	currentGameState = TITLE_SCREEN;
	
	resolution = sf::Vector2f(1000.f, 750.f);
	video = sf::VideoMode(resolution.x, resolution.y);

	// Create render window and set framerate.
	window = std::make_shared<sf::RenderWindow>(video, "Cube");
	window->setFramerateLimit(60);

	playerView = std::make_shared<sf::View>(
			sf::Vector2f(0.5 * resolution.x, 0.5 * resolution.y),
			sf::Vector2f(resolution.x, resolution.y)
		);
	playerView->setViewport(sf::FloatRect(-0.f, -0.f, 1.f, 1.f));
}


