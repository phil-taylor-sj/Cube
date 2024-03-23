#include "Scenes/TitleScene.h"

namespace Scenes
{
	TitleSceneActions TitleScene::checkInput(sf::Keyboard::Key key)
	{
		if (m_availableKeyActions.count(key) > 0)
		{
			return m_availableKeyActions[key];
		}
		else
		{
			return TitleSceneActions::NONE;
		}
	}

	void TitleScene::processAction(Engine::Action<TitleSceneActions> action)
	{
		switch (action.getName())
		{
		case TitleSceneActions::START:
			m_nextScene = SceneNames::LEVEL;
			break;
		case TitleSceneActions::SET_CURSOR:
			if (action.checkProperty("x") && action.checkProperty("y"))
			{
				m_cursorPosition = Physics::Vec2f(
					action.getProperty("x"),
					action.getProperty("y")
				);
			}
			break;
		case TitleSceneActions::EXIT:
			m_window->close();
			break;
		default:
			break;
		}
	}

	void TitleScene::renderScene()
	{
		m_window->setView(*m_view);
		m_window->draw(m_currentBackground);
	}

	void TitleScene::updateScene()
	{
			
	}

	void TitleScene::setDeltaTime(float deltaTime)
	{
		float m_deltaTime = deltaTime;
	}

	void TitleScene::setWindowSize(float xSize, float ySize)
	{
		m_windowSize = Physics::Vec2f(xSize, ySize);
	}

	SceneNames TitleScene::checkNextScene()
	{
		SceneNames nextScene = m_nextScene;
		m_nextScene = SceneNames::NONE;
		return nextScene;
	}



	TitleScene::TitleScene()
	{
		
	}

}