#include "Scenes/GameOverScene.h"

namespace Scenes
{
	SceneActions GameOverScene::checkInput(sf::Keyboard::Key key)
	{
		if (m_availableKeyActions.count(key) > 0)
		{
			return m_availableKeyActions[key];
		}
		else
		{
			return SceneActions::NONE;
		}
	}

	void GameOverScene::processAction(Engine::Action action)
	{
		switch (action.getName())
		{
		case SceneActions::EXIT:
			m_window->close();
			break;
		default:
			break;
		}
	}

	void GameOverScene::renderScene()
	{
		m_window->setView(*m_view);
		m_window->draw(m_currentBackground);
		m_window->draw(m_mainText);
	}

	void GameOverScene::updateScene()
	{
		m_sceneTime += m_deltaTime;
		if (m_sceneTime >= m_sceneTimeLimit)
		{
			m_nextScene = SceneNames::TITLE;
		}

		m_resizeBackground();
		m_mainText.setPosition(0.5f * m_window->getSize().x, 0.5f * m_window->getSize().y);

		m_textTime += m_deltaTime;
		m_textTime = std::min(m_textTime, m_textPeriod);
		int opacity = 225.f * m_textTime / m_textPeriod;
		m_mainText.setColor(sf::Color(255, 255, 255, opacity));
		m_mainText.setOutlineColor(sf::Color(0, 0, 0, opacity));
		m_mainText.setOutlineThickness(3);
	}

	void GameOverScene::setDeltaTime(float deltaTime)
	{
		m_deltaTime = deltaTime;
	}

	GameOverScene::GameOverScene()
	{
		Assets::FontDict::getInstance()->loadFont("Tuffy");
		m_mainText.setFont(
			Assets::FontDict::getInstance()->getFont("Tuffy")
		);
		m_mainText.setString(sf::String("'There is no way out of here...'"));
		m_mainText.setPosition(500, 500);
		m_mainText.setOrigin(
			0.5f * m_mainText.getGlobalBounds().width,
			0.5f * m_mainText.getGlobalBounds().height
		);

		//m_mainText.setColor(sf::Color(255, 255, 255, 128));

		Assets::TextureDict::getInstance()->loadTexture("GameOverBackground");
		m_currentBackground.setTexture(
			Assets::TextureDict::getInstance()->getTexture("GameOverBackground")
		);

	}

	void GameOverScene::m_resizeBackground()
	{
		float scale = m_window->getSize().y / m_currentBackground.getGlobalBounds().height;
		m_currentBackground.scale(scale, scale);

		float width = m_currentBackground.getGlobalBounds().width;
		//float offset = (0.5f * width) - (0.5f * m_window->getSize().x);
		//m_currentBackground.setPosition(-offset, 0);	
	}
}