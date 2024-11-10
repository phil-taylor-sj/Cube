#pragma once
#include "Scenes/Scene.h"
#include "Scenes/GameSceneActions.h"
#include "Assets/TextureDict.h"
#include "Assets/FontDict.h"

#include <VecPlus/Vec2.h>


namespace Scenes
{
	class TitleScene : public Scene
	{
	public:
		SceneActions checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action) override;
		void updateScene() override;
		void renderScene() override;
		void setDeltaTime(float deltaTime) override;

		TitleScene();

	private:
		sf::Sprite m_currentBackground;
		std::map<sf::Keyboard::Key, SceneActions> m_availableKeyActions
		{
			{ sf::Keyboard::Space, SceneActions::START},
			{ sf::Keyboard::Escape, SceneActions::EXIT}
		};
		vecp::Vec2f m_cursorPosition;
		sf::Text m_mainText;
		sf::Text m_titleText;
		float m_deltaTime = 0.001;
		float m_textPeriod = 2.f;
		float m_textTime = 0.f;

		void m_resizeBackground();
	};
}