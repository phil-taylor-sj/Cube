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

	template<typename T>
	void Action<T>::setProperty(std::string property, float value)
	{
		m_properties.insert({property, value});
	}

	template<typename T>
	float Action<T>::getProperty(std::string property)
	{
		return m_properties.find(property)->second;
	}

	template<typename T>
	bool Action<T>::checkProperty(std::string property)
	{
		return m_properties.count(property) > 0;
	}

	template<typename T>
	void setProperty(std::string property, float value)
	{
		m_properties.insert({ property, value });
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

template class Engine::Action<Scenes::GameSceneActions>;