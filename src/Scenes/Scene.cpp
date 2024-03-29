#include "Scenes/Scene.h"

namespace Scenes
{
	template <typename T>
	void Scene<T>::setRenderWindow(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
	}

	template <typename T>
	void Scene<T>::setView(std::shared_ptr<sf::View> view)
	{
		m_view = view;
	}

	template <typename T>
	Scene<T>::Scene<T>()
	{

	}
}

template class Scenes::Scene<Scenes::GameSceneActions>::Scene;

template class Scenes::Scene<Scenes::TitleSceneActions>::Scene;