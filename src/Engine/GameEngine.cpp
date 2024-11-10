#include "Engine/GameEngine.h"


namespace Engine
{
	void GameEngine::runEngine()
	{
		Engine::Inputs inputs = Engine::Inputs();
		inputs.setWindow(window);
		inputs.setPlayerView(playerView);

		m_lastDeltaTime = 0.016f;
		
		while (window->isOpen())
		{
			Scenes::SceneNames nextScene = m_currentScene->checkNextScene();
			if (nextScene != Scenes::SceneNames::NONE)
			{
				switch (nextScene)
				{
				case Scenes::SceneNames::LEVEL:
					m_currentScene = std::make_unique<Scenes::GameScene>();
					break;
				default:
					break;
				}
				m_currentScene->setRenderWindow(window);
				m_currentScene->setView(playerView);
			}
			

			m_frameTimer.restart();
			m_currentScene->setDeltaTime(m_lastDeltaTime);

			inputs.getInputs(*this);
			m_currentScene->updateScene();

			window->clear();
			m_currentScene->renderScene();

			window->setView(*playerView);
			window->display();
			
			m_lastDeltaTime = m_frameTimer.getElapsedTime().asSeconds();
		}
	}

	void GameEngine::checkInput(sf::Keyboard::Key key, sf::Event::EventType eventType)
	{
		//if (typeid(*m_currentScene) == typeid(Scenes::GameScene))
		if (m_currentScene != nullptr)
		{
			Scenes::SceneActions sceneAction = m_currentScene->checkInput(key);
			if (sceneAction != Scenes::SceneActions::NONE)
			{
				ActionType type = (eventType == sf::Event::KeyPressed) ? PRESS : RELEASE;
				Action newAction = Action(sceneAction, type);
				m_currentScene->processAction(newAction);
			}
		}
	}

	void GameEngine::sendCursorPosition(float xCursor, float yCursor)
	{
		if (typeid(*m_currentScene) == typeid(Scenes::GameScene))
		{
			Action newAction = Action(
				Scenes::SceneActions::SET_CURSOR, Engine::ActionType::NONE
			);
			newAction.setProperty("x", xCursor);
			newAction.setProperty("y", yCursor);
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
	
		m_currentScene = std::make_unique<Scenes::TitleScene>();
		m_currentScene->setRenderWindow(window);
		m_currentScene->setView(playerView);
	}
}