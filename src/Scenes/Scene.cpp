#include "Scenes/Scene.h"

namespace Scenes
{
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