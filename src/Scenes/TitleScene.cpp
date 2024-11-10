#include "Scenes/TitleScene.h"

namespace Scenes
{
	GameSceneActions TitleScene::checkInput(sf::Keyboard::Key key)
	{
		if (m_availableKeyActions.count(key) > 0)
		{
			return m_availableKeyActions[key];
		}
		else
		{
			return GameSceneActions::NONE;
		}
	}

	void TitleScene::processAction(Engine::Action action)
	{
		switch (action.getName())
		{
		case GameSceneActions::START:
			m_nextScene = SceneNames::LEVEL;
			break;
		case GameSceneActions::SET_CURSOR:
			if (action.checkProperty("x") && action.checkProperty("y"))
			{
				m_cursorPosition = vecp::Vec2f(
					action.getProperty("x"),
					action.getProperty("y")
				);
			}
			break;
		case GameSceneActions::EXIT:
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
		m_window->draw(m_mainText);
	}

	void TitleScene::updateScene()
	{
		m_textTime += m_deltaTime;
		if (m_textTime > m_textPeriod)
		{
			m_textTime = 0.f;
		}
		int opacity = static_cast<int>(255.f * m_textTime / m_textPeriod);
		m_mainText.setColor(sf::Color(255, 255, 255, opacity));

	}

	void TitleScene::setDeltaTime(float deltaTime)
	{
		m_deltaTime = deltaTime;
	}

	void TitleScene::setWindowSize(float xSize, float ySize)
	{
		m_windowSize = vecp::Vec2f(xSize, ySize);
	}

	TitleScene::TitleScene()
	{
		Assets::FontDict::getInstance()->loadFont("Tuffy");
		m_mainText.setFont(
			Assets::FontDict::getInstance()->getFont("Tuffy")
		);
		m_mainText.setString(sf::String("Press Space To Start"));
		m_mainText.setPosition(100,100);

		//m_mainText.setColor(sf::Color(255, 255, 255, 128));
		

		Assets::TextureDict::getInstance()->loadTexture("TitleBackground");
		m_currentBackground.setTexture(
			Assets::TextureDict::getInstance()->getTexture("TitleBackground")
		);
	}

}