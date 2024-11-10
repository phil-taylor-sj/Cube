#include "Scenes/Scene.h"

namespace Scenes
{
	SceneNames Scene::checkNextScene()
	{
		SceneNames nextScene = m_nextScene;
		m_nextScene = SceneNames::NONE;
		return nextScene;
	}

	void Scene::setRenderWindow(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
	}

	void Scene::setView(std::shared_ptr<sf::View> view)
	{
		m_view = view;
	}

	Scene::Scene()
	{

	}
}