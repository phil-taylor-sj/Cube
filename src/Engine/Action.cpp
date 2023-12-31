#include "Engine/Action.h"

namespace Engine
{
	template <typename T>
	const T& Action<T>::getName() const
	{
		return m_name;
	}

	template <typename T>
	const ActionType& Action<T>::getType() const
	{
		return m_type;
	}

	template <typename T>
	Action<T>::Action<T>(T name, ActionType type)
	{
		m_name = name;
		m_type = type;
	}

	template <typename T>
	Action<T>::~Action<T>()
	{

	}
}

template class Engine::Action<Scenes::GameSceneActionNames>;