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
			case GameSceneActions::SET_CURSOR:
				if (action.checkProperty("x") && action.checkProperty("y"))
				{
					m_cursorPosition = Physics::Vec2f(
						action.getProperty("x"),
						action.getProperty("y")
						);
				}
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
		m_level->renderBackground(*m_window);
		m_level->renderLevel(*m_window);
		m_actors->renderActors(*m_window);
	}

	void GameScene::updateScene()
	{
		this->m_setPlayerAngle();
		//this->m_cursorPosition -= m_actors->transformComponents[0].position;
		m_cursorPosition.x -= 0.5f * m_window->getSize().x;
		m_cursorPosition.y -= 0.5f * m_window->getSize().y;
		
		float playerAngle = Utilities::VecMath<float>::angleBetweenVectors(
			m_cursorPosition, Physics::Vec2f(100.f, 0.f)
		);
		if (m_cursorPosition.y < 0.f)
		{
			playerAngle = 360.f - playerAngle;
		}

		m_actors->transformComponents[0].angle = playerAngle;
		Actors::ActorEntitySystem::applyMovementForce(m_actors->forceComponents);

		m_level->processLevelShift();
		m_level->updateAllCellScaling();
		m_actors->moveActors(0.1f);
		m_processCollisions();
		m_actors->updateGraphics();
		m_level->clearForces();
	
	}

	void GameScene::setDeltaTime(float deltaTime)
	{
		Levels::LevelEntitySystem::setDeltaTime(deltaTime);
	}

	GameScene::GameScene()
	{
		m_level = std::make_unique<Levels::LevelEntityManager>(4, 4);
		m_level->setCommonCellWidth(512.f);
		m_level->updateAllCellScaling();

		// Make an actor for the player (always set to index 0)
		m_actors = std::make_unique<Actors::ActorEntityManager>();
		m_actors->setReferenceLength(m_level->getCommonCellWidth());
		m_actors->assignActor(Actors::ActorTypes::PLAYER, Actors::ActorSubtypes::NONE);

		
		Physics::Vec2i gridSize = m_level->getGridSize() - 2;
		m_actors->transformComponents[0].position = Physics::Vec2f(
			(rand() % gridSize.x + 1 + 0.5f) * m_level->getCommonCellWidth(),
			(rand() % gridSize.y + 1 + 0.5f) * m_level->getCommonCellWidth()
		);
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

	void GameScene::m_processCollisions()
	{
		int actorId = 0;
		for (const Actors::ActorEntity& actor : m_actors->entities)
		{
			if (!actor.isAssigned)
			{
				continue;
			}

			const Levels::DetectedLevelCollisions levelCollisions = 
				m_level->getCircleCollisions(
					m_actors->collisionComponents[actorId]
				);

			if (levelCollisions.isFloorDetected == false)
			{

			}

			if (actor.components.test(Actors::ActorComponentTypes::GRAVITY))
			{
				if (!m_actors->gravityComponents[actorId].isFalling)
				{
					m_actors->gravityComponents[actorId].isFalling = !levelCollisions.isFloorDetected;				
				}
				else
				{
					continue;
				}
				
				Actors::ActorEntitySystem::applyFloorMovement(
					m_actors->transformComponents[actorId],
					m_actors->collisionComponents[actorId],
					levelCollisions.floorForce
				);
			}

			if (levelCollisions.staticWalls.size() > 0)
			{
				Actors::ActorEntitySystem::applyWallCollisions(
					m_actors->transformComponents[actorId],
					m_actors->collisionComponents[actorId],
					levelCollisions.staticWalls
				);
			}


			actorId++;	
		}
	}

}