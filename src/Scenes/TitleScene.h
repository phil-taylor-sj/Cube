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
		GameSceneActions checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action) override;
		void updateScene() override;
		void renderScene() override;
		void setDeltaTime(float deltaTime) override;

		void setWindowSize(float xSize, float ySize);

		TitleScene();

	private:
		vecp::Vec2f m_windowSize;
		sf::Sprite m_currentBackground;
		std::map<sf::Keyboard::Key, GameSceneActions> m_availableKeyActions
		{
			{ sf::Keyboard::Space, GameSceneActions::START},
			{ sf::Keyboard::Escape, GameSceneActions::EXIT}
		};
		vecp::Vec2f m_cursorPosition;
		sf::Text m_mainText;
		float m_deltaTime = 0.001;
		float m_textPeriod = 3.f;
		float m_textTime = 0.f;
	};
}