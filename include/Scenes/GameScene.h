#pragma once
#include <SFML/Graphics.hpp>
#include "Actors/ActorEntityManager.h"
#include "Levels/LevelEntityManager.h"
#include "Scenes/Scene.h"
#include "Assets/TextureDict.h"
#include "Scenes/GameSceneAction.h"
#include "Engine/Action.h"

namespace Scenes
{
	class GameScene : public Scene<GameSceneActionNames>
	{
	public:
		GameSceneActionNames checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action<GameSceneActionNames>) override;
		void updateScene() override;
		void renderScene() override;

		GameScene();

	private:
		std::unique_ptr<Levels::LevelEntityManager> m_level;
		std::unique_ptr<Actors::ActorEntityManager> m_actors;
		std::map<sf::Keyboard::Key, GameSceneActionNames> m_actions;
	
		std::map<GameSceneActionNames, bool> m_playerMovement;

		void m_setPlayerMovement(Engine::Action<GameSceneActionNames> action);
		void m_setPlayerAngle();
	};
}