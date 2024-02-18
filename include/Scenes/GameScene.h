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
	class GameScene : public Scene<GameSceneActions>
	{
	public:
		GameSceneActions checkInput(sf::Keyboard::Key) override;
		void processAction(Engine::Action<GameSceneActions>) override;
		void updateScene() override;
		void renderScene() override;
		void setDeltaTime(float deltaTime) override;

		GameScene();

	private:
		std::unique_ptr<Levels::LevelEntityManager> m_level;
		std::unique_ptr<Actors::ActorEntityManager> m_actors;
		std::map<sf::Keyboard::Key, GameSceneActions> m_availableKeyActions 
		{
			{ sf::Keyboard::W, GameSceneActions::MOVE_UP },
			{ sf::Keyboard::S, GameSceneActions::MOVE_DOWN },
			{ sf::Keyboard::A, GameSceneActions::MOVE_LEFT },
			{ sf::Keyboard::D, GameSceneActions::MOVE_RIGHT },
			{ sf::Keyboard::Escape, GameSceneActions::EXIT }
		};
	
		std::map<GameSceneActions, bool> m_playerMoves
		{
			{GameSceneActions::MOVE_UP, false},
			{GameSceneActions::MOVE_DOWN, false},
			{GameSceneActions::MOVE_LEFT, false},
			{GameSceneActions::MOVE_RIGHT, false}
		};

		Physics::Vec2f m_cursorPosition;

		void m_setPlayerMovement(Engine::Action<GameSceneActions> action);
		void m_setPlayerAngle();
		void m_processCollisions();
	};
}