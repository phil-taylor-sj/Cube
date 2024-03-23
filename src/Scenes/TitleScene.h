#pragma once
#include "Scenes/Scene.h"
#include "Scenes/TitleSceneActions.h"
#include "Physics/Vec2.h"

namespace Scenes
{
	class TitleScene : public Scene<TitleSceneActions>
	{
	public:
		TitleSceneActions checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action<TitleSceneActions>) override;
		void updateScene() override;
		void renderScene() override;
		void setDeltaTime(float deltaTime) override;

		void setWindowSize(float xSize, float ySize);
		SceneNames checkNextScene();

		TitleScene();

	private:
		Physics::Vec2f m_windowSize;
		sf::Sprite m_currentBackground;
		std::map<sf::Keyboard::Key, TitleSceneActions> m_availableKeyActions
		{
			{ sf::Keyboard::W, TitleSceneActions::START},
			{ sf::Keyboard::Escape, TitleSceneActions::EXIT }
		};
		Physics::Vec2f m_cursorPosition;
		SceneNames m_nextScene;
		float m_deltaTime;
	};
}