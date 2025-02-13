#include "Scenes/GameScene.h"

namespace Scenes
{
	 SceneActions GameScene::checkInput(sf::Keyboard::Key key)
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

	 void GameScene::processAction(Engine::Action action)
	 {
		 switch (action.getName())
		 {
			case SceneActions::MOVE_UP:
			case SceneActions::MOVE_DOWN:
			case SceneActions::MOVE_LEFT:
			case SceneActions::MOVE_RIGHT:
				m_setPlayerMovement(action);
				break;
			case SceneActions::SET_CURSOR:
				if (action.checkProperty("x") && action.checkProperty("y"))
				{
					m_cursorPosition = Physics::Vec2f(
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

	 void GameScene::renderScene()
	{
		m_view->setCenter(
			m_actors->transformComponents[0].position.x,
			m_actors->transformComponents[0].position.y
		);
		m_window->setView(*m_view);
		m_level->renderBackground(*m_window);
		m_actors->renderBackgroundActors(*m_window);
		m_level->renderLevel(*m_window);
		m_actors->renderForegroundActors(*m_window);
	}

	void GameScene::updateScene()
	{
		this->m_setPlayerAngle();
		//this->m_cursorPosition -= m_actors->transformComponents[0].position;
		m_cursorPosition.x -= 0.5f * m_window->getSize().x;
		m_cursorPosition.y -= 0.5f * m_window->getSize().y;
		
		/*
		float playerAngle = Utilities::VecMath<float>::angleBetweenVectors(
			m_cursorPosition, Physics::Vec2f(100.f, 0.f)
		);
		if (m_cursorPosition.y < 0.f)
		{
			playerAngle = 360.f - playerAngle;
		}
		**/

		m_actors->transformComponents[0].angle = m_actors->forceComponents[0].movementAngle;
		Actors::ActorEntitySystem::applyMovementForce(m_actors->forceComponents);

		m_level->updateLevel();
		m_actors->moveActors(0.1f);
		m_processCollisions();
		m_actors->updateGraphics();
		m_level->clearForces();
		m_actors->updateActorState();

		if (m_actors->typeComponents[0].actorState == Actors::ActorTypeComponent::DEAD)
		{
			m_nextScene = SceneNames::GAME_OVER;
		}
	}

	void GameScene::setDeltaTime(float deltaTime)
	{
		Levels::LevelEntitySystem::setDeltaTime(deltaTime);
		Actors::ActorEntitySystem::setDeltaTime(deltaTime);
	}

	GameScene::GameScene()
	{
		Levels::LevelSettings settings{};
		settings.size.x = 4;
		settings.size.y = 4;
		settings.cellWidth = 512.f;
		m_level = std::make_unique<Levels::LevelEntityManager>(settings);

		// Make an actor for the player (always set to index 0)
		m_actors = std::make_unique<Actors::ActorEntityManager>();
		m_actors->setReferenceLength(m_level->getCommonCellWidth());
		m_actors->assignActor(Actors::ActorTypes::PLAYER, Actors::ActorSubtypes::NONE);

		
		vecp::Vec2i gridSize = m_level->getGridSize() - 2;
		m_actors->transformComponents[0].position = vecp::Vec2f(
			(rand() % gridSize.x + 1 + 0.5f) * m_level->getCommonCellWidth(),
			(rand() % gridSize.y + 1 + 0.5f) * m_level->getCommonCellWidth()
		);
	}

	void GameScene::m_setPlayerMovement(Engine::Action action)
	{
		m_playerMoves[action.getName()] = (action.getType() == Engine::PRESS) ? true : false;

		if (action.getType() == Engine::PRESS)
		{	
			std::map<SceneActions, SceneActions> opposites
			{
				{SceneActions::MOVE_UP, SceneActions::MOVE_DOWN},
				{SceneActions::MOVE_DOWN, SceneActions::MOVE_UP},
				{SceneActions::MOVE_LEFT, SceneActions::MOVE_RIGHT},
				{SceneActions::MOVE_RIGHT, SceneActions::MOVE_LEFT}
			};

			m_playerMoves[opposites[action.getName()]] = false;
		}
	}

	void GameScene::m_setPlayerAngle()
	{
		std::map<SceneActions, float> movementAngles
		{
			{SceneActions::MOVE_RIGHT, 0.f}, {SceneActions::MOVE_DOWN, 90.f},
			{SceneActions::MOVE_LEFT, 180.f}, {SceneActions::MOVE_UP, 270.f}
		};

		int counter = 0;
		float angle = 0.f;
		for (const std::pair<SceneActions, float>& action : movementAngles)
		{
			if (m_playerMoves[action.first])
			{
				angle += action.second;
				counter += 1;
			}
		}

		if (m_playerMoves[SceneActions::MOVE_UP] &&
			m_playerMoves[SceneActions::MOVE_RIGHT])
		{
			angle += 360.f;
		}

		angle = angle / std::max(counter, 1);
		
		// Don't apply movement inputs if player is 
		if (m_actors->gravityComponents[0].ActorState !=
			Actors::ActorGravityComponent::FALLING)
		{
			m_actors->forceComponents[0].isMoving = counter > 0;
			if (counter > 0) {m_actors->forceComponents[0].movementAngle = angle;} 
		}
		else
		{
			m_actors->forceComponents[0].isMoving = false;
		}
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
				if (m_actors->gravityComponents[actorId].ActorState == 
						Actors::ActorGravityComponent::STEADY && !levelCollisions.isFloorDetected)
				{	
					m_actors->gravityComponents[actorId].voidCentre = levelCollisions.voidCentre;
					m_actors->gravityComponents[actorId].ActorState = 
						Actors::ActorGravityComponent::FALLING;				
				}

				if (m_actors->gravityComponents[actorId].ActorState !=
					Actors::ActorGravityComponent::STEADY)
				{
					Actors::ActorEntitySystem::adjustGravityMotion(
						m_actors->gravityComponents[actorId],
						m_actors->transformComponents[actorId]);
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

			if (levelCollisions.blockers.size() > 0 &&
				m_actors->typeComponents[actorId].type == Actors::ActorTypes::PLAYER)
			{
				Actors::ActorEntitySystem::applyWallCollisions(
					m_actors->transformComponents[actorId],
					m_actors->collisionComponents[actorId],
					levelCollisions.blockers
				);
			}


			actorId++;	
		}


	}

}