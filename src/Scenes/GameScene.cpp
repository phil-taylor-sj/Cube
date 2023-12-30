#include "Scenes/GameScene.h"

namespace Scenes
{
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
	}

}