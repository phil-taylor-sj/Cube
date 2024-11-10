#pragma once
#include <SFML/Graphics.hpp>
#include "math.h"
#include "Actors/ActorEntityManager.h"
#include "Actors/ActorEntity.h"
#include "Actors/ActorComponents.h"
#include "Levels/LevelEntityManager.h"
#include "Levels/LevelEntitySystem.h"
#include "Scenes/Scene.h"
#include "Assets/TextureDict.h"
#include "Scenes/GameSceneActions.h"
#include "Engine/Action.h"
#include "Actors/ActorEntitySystem.h"
#include "Utilities/VecMath.h"

namespace Scenes
{
	class GameScene : public Scene
	{
	public:
		SceneActions checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action) override;
		void updateScene() override;
		void renderScene() override;
		void setDeltaTime(float deltaTime) override;

		GameScene();

	private:
		std::unique_ptr<Levels::LevelEntityManager> m_level;
		std::unique_ptr<Actors::ActorEntityManager> m_actors;
		std::map<sf::Keyboard::Key, SceneActions> m_availableKeyActions 
		{
			{ sf::Keyboard::W, SceneActions::MOVE_UP },
			{ sf::Keyboard::S, SceneActions::MOVE_DOWN },
			{ sf::Keyboard::A, SceneActions::MOVE_LEFT },
			{ sf::Keyboard::D, SceneActions::MOVE_RIGHT },
			{ sf::Keyboard::Escape, SceneActions::EXIT }
		};
	
		std::map<SceneActions, bool> m_playerMoves
		{
			{SceneActions::MOVE_UP, false},
			{SceneActions::MOVE_DOWN, false},
			{SceneActions::MOVE_LEFT, false},
			{SceneActions::MOVE_RIGHT, false}
		};

		Physics::Vec2f m_cursorPosition;

		void m_setPlayerMovement(Engine::Action action);
		void m_setPlayerAngle();
		void m_processCollisions();
	};
}