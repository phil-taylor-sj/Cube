#pragma once
#include <SFML/Graphics.hpp>
#include "Actors/ActorEntityManager.h"
#include "Levels/LevelEntityManager.h"
#include "Scenes/Scene.h"
#include "Assets/TextureDict.h"


namespace Scenes
{
	class GameScene : public Scene
	{
	public:
		void updateScene() override;
		void renderScene() override;

		GameScene();

	private:
		std::unique_ptr<Levels::LevelEntityManager> m_level;
		std::unique_ptr<Actors::ActorEntityManager> m_actors;

	};
}