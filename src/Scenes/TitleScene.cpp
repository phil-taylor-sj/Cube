#include "Scenes/TitleScene.h"

namespace Scenes
{
	SceneActions TitleScene::checkInput(sf::Keyboard::Key key)
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

	void TitleScene::processAction(Engine::Action action)
	{
		switch (action.getName())
		{
		case SceneActions::START:
			m_nextScene = SceneNames::LEVEL;
			break;
		case SceneActions::SET_CURSOR:
			if (action.checkProperty("x") && action.checkProperty("y"))
			{
				m_cursorPosition = vecp::Vec2f(
					action.getProperty("x"),
					action.getProperty("y")
				);
			}
			break;
		case SceneActions::EXIT:
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
		m_resizeBackground();
		m_textTime += m_deltaTime;
		if (m_textTime > m_textPeriod)
		{
			m_textTime = 0.f;
		}
		int opacity = (m_textTime < 0.5f * m_textPeriod) ? 255.f : 0.f;
		m_mainText.setColor(sf::Color(255, 255, 255, opacity));
		m_mainText.setOutlineColor(sf::Color(0, 0, 0, opacity));
		m_mainText.setOutlineThickness(3);
	}

	void TitleScene::setDeltaTime(float deltaTime)
	{
		m_deltaTime = deltaTime;
	}

	TitleScene::TitleScene()
	{
		Assets::FontDict::getInstance()->loadFont("Tuffy");
		m_mainText.setFont(
			Assets::FontDict::getInstance()->getFont("Tuffy")
		);
		m_mainText.setString(sf::String("Press Space To Start"));
		m_mainText.setPosition(500,500);

		//m_mainText.setColor(sf::Color(255, 255, 255, 128));
		
		Assets::TextureDict::getInstance()->loadTexture("TitleBackground");
		m_currentBackground.setTexture(
			Assets::TextureDict::getInstance()->getTexture("TitleBackground")
		);

	}

	void TitleScene::m_resizeBackground()
	{
		float scale = m_window->getSize().y / m_currentBackground.getGlobalBounds().height;
		m_currentBackground.scale(scale, scale);		
	
		float width = m_currentBackground.getGlobalBounds().width;
		float offset = (0.5f * width) - (0.5f * m_window->getSize().x);
		m_currentBackground.setPosition(-offset, 0);
	}

}