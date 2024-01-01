#include "Scenes/GameScene.h"

namespace Scenes
{
	 GameSceneActions GameScene::checkInput(sf::Keyboard::Key key)
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

	 void GameScene::processAction(Engine::Action<GameSceneActions> action)
	 {
		 switch (action.getName())
		 {
			case GameSceneActions::MOVE_UP:
			case GameSceneActions::MOVE_DOWN:
			case GameSceneActions::MOVE_LEFT:
			case GameSceneActions::MOVE_RIGHT:
				m_setPlayerMovement(action);
				break;
			case GameSceneActions::EXIT:
				m_window->close();
				break;
			default:
				break;
		 }
	 }

	 void GameScene::renderScene()
	{
		m_view->setCenter(
			m_actors->transformComponents[0].position.x,
			m_actors->transformComponents[0].position.y
		);
		m_window->setView(*m_view);
		m_level->renderLevel(*m_window);
		m_actors->renderActors(*m_window);
	}

	void GameScene::updateScene()
	{
		this->m_setPlayerAngle();
		Actors::ActorEntitySystem::applyMovementForce(m_actors->forceComponents);
		m_actors->updateActors(0.1f);
	}

	GameScene::GameScene()
	{
		m_level = std::make_unique<Levels::LevelEntityManager>(5, 5);
		m_level->setCommonCellWidth(512.f);
		m_level->updateAllCellScaling();

		m_actors = std::make_unique<Actors::ActorEntityManager>();

		m_actors->assignActor(Actors::ActorTypes::PLAYER, Actors::ActorSubtypes::NONE);
		m_actors->transformComponents[0].position = Physics::Vec2f(64.f * 2.5f, 64.f * 2.5f);
	}

	void GameScene::m_setPlayerMovement(Engine::Action<GameSceneActions> action)
	{
		m_playerMoves[action.getName()] = (action.getType() == Engine::PRESS) ? true : false;

		if (action.getType() == Engine::PRESS)
		{	
			std::map<GameSceneActions, GameSceneActions> opposites
			{
				{GameSceneActions::MOVE_UP, GameSceneActions::MOVE_DOWN},
				{GameSceneActions::MOVE_DOWN, GameSceneActions::MOVE_UP},
				{GameSceneActions::MOVE_LEFT, GameSceneActions::MOVE_RIGHT},
				{GameSceneActions::MOVE_RIGHT, GameSceneActions::MOVE_LEFT}
			};

			m_playerMoves[opposites[action.getName()]] = false;
		}
	}

	void GameScene::m_setPlayerAngle()
	{
		std::map<GameSceneActions, float> movementAngles
		{
			{GameSceneActions::MOVE_RIGHT, 0.f}, {GameSceneActions::MOVE_DOWN, 90.f},
			{GameSceneActions::MOVE_LEFT, 180.f}, {GameSceneActions::MOVE_UP, 270.f}
		};

		int counter = 0;
		float angle = 0.f;
		for (const std::pair<GameSceneActions, float>& action : movementAngles)
		{
			if (m_playerMoves[action.first])
			{
				angle += action.second;
				counter += 1;
			}
		}

		if (m_playerMoves[GameSceneActions::MOVE_UP] &&
			m_playerMoves[GameSceneActions::MOVE_RIGHT])
		{
			angle += 360.f;
		}

		angle = angle / std::max(counter, 1);
		m_actors->forceComponents[0].isMoving = counter > 0;
		m_actors->forceComponents[0].movementAngle = angle; 
	}

}