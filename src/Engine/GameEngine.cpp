#include "Engine/GameEngine.h"


namespace Engine
{
	void GameEngine::runEngine()
	{
		Engine::Inputs inputs = Engine::Inputs();
		inputs.setWindow(window);
		inputs.setPlayerView(playerView);

		while (window->isOpen())
		{
			inputs.getInputs(*this);
			m_currentScene->updateScene();
			window->clear();
			m_currentScene->renderScene();
			window->setView(*playerView);
			window->display();
		}
	}

	void GameEngine::checkInput(sf::Keyboard::Key key, sf::Event::EventType eventType)
	{
		if (typeid(*m_currentScene) == typeid(Scenes::GameScene))
		{
			Scenes::GameSceneActionNames sceneAction = m_currentScene->checkInput(key);
			ActionType type = (eventType == sf::Event::KeyPressed) ? PRESS : RELEASE;

			Action newAction = Action<Scenes::GameSceneActionNames>(sceneAction, type);
			m_currentScene->processAction(newAction);
		}
	}

	GameEngine::GameEngine()
	{
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
	
		m_currentScene = std::make_unique<Scenes::GameScene>();
		m_currentScene->setRenderWindow(window);
		m_currentScene->setView(playerView);
	}
}