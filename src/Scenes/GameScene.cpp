#include "Scenes/GameScene.h"

namespace Scenes
{
	 GameSceneActionNames GameScene::checkInput(sf::Keyboard::Key key)
	 {
		 if (m_actions.count(key) > 0)
		 {
			 return m_actions[key];
		 }
		 else
		 {
			 return NONE;
		 }
	 }

	 void GameScene::processAction(Engine::Action<GameSceneActionNames> action)
	 {
		 if (action.getName() == MOVE_UP ||
			 action.getName() == MOVE_DOWN ||
			 action.getName() == MOVE_LEFT ||
			 action.getName() == MOVE_RIGHT)
		 {
			 m_setPlayerMovement(action);
		 }

		 if (action.getName() == EXIT)
		 {
			 m_window->close();
		 }
	 }

	 void GameScene::renderScene()
	{
		m_view->setCenter(
			m_actors->transformComponents[0].position.x,
			m_actors->transformComponents[0].position.y
		);
		m_level->renderLevel(*m_window);
		m_actors->renderActors(*m_window);
	}

	void GameScene::updateScene()
	{
		
		m_actors->updateActors(10.f);
	}

	GameScene::GameScene()
	{
		m_level = std::make_unique<Levels::LevelEntityManager>(5, 5);
		m_level->setCommonCellWidth(512.f);
		m_level->updateAllCellScaling();

		m_actors = std::make_unique<Actors::ActorEntityManager>();

		m_actors->assignActor("Player", "None");
		Assets::TextureDict::getInstance()->loadTexture("PlayerPlaceholder");
		m_actors->graphicsComponents[0].sprite.setTexture(
			Assets::TextureDict::getInstance()->getTexture("PlayerPlaceholder")
		);

		m_actors->transformComponents[0].position = Physics::Vec2f(64.f * 2.5f, 64.f * 2.5f);
	
		m_actions.insert({ sf::Keyboard::W, MOVE_UP });
		m_actions.insert({ sf::Keyboard::S, MOVE_DOWN });
		m_actions.insert({ sf::Keyboard::A, MOVE_LEFT });
		m_actions.insert({ sf::Keyboard::D, MOVE_RIGHT });
		m_actions.insert({ sf::Keyboard::Escape, EXIT });

		m_playerMovement.insert({ MOVE_UP, false });
		m_playerMovement.insert({ MOVE_DOWN, false });
		m_playerMovement.insert({ MOVE_LEFT, false });
		m_playerMovement.insert({ MOVE_RIGHT, false });
	}

	void GameScene::m_setPlayerMovement(Engine::Action<GameSceneActionNames> action)
	{
		m_playerMovement[action.getName()] = (action.getType() == Engine::PRESS) ? true : false;

		if (action.getType() == Engine::PRESS)
		{
			if (action.getName() == MOVE_UP)
			{
				m_playerMovement[MOVE_DOWN] == false;
			}
			if (action.getName() == MOVE_DOWN)
			{
				m_playerMovement[MOVE_UP] == false;
			}
			if (action.getName() == MOVE_RIGHT)
			{
				m_playerMovement[MOVE_RIGHT] == false;
			}
			if (action.getName() == MOVE_LEFT)
			{
				m_playerMovement[MOVE_LEFT] == false;
			}
		}
	}

	void GameScene::m_setPlayerAngle()
	{

	}

}