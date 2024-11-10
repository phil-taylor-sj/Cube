#pragma once

#include "Scenes/Scene.h"

#include "Assets/TextureDict.h"
#include "Assets/FontDict.h"

#include <VecPlus/Vec2.h>

namespace Scenes
{
	class GameOverScene : public Scene
	{
	public:
		SceneActions checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action) override;
		void updateScene() override;
		void renderScene() override;
		void setDeltaTime(float deltaTime) override;

		GameOverScene();

	private:
		sf::Sprite m_currentBackground;
		std::map<sf::Keyboard::Key, SceneActions> m_availableKeyActions
		{
			{ sf::Keyboard::Escape, SceneActions::EXIT}
		};
		vecp::Vec2f m_cursorPosition;
		sf::Text m_mainText;
		float m_deltaTime = 0.001;
		float m_textTime = 0.f;
		float m_textPeriod = 0.f;
		float m_sceneTimeLimit = 1.f;
		float m_sceneTime = 0.f;

		void m_resizeBackground();
	};
}