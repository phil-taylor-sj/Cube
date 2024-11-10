#include "Engine/Action.h"

namespace Engine
{
	const Scenes::GameSceneActions& Action::getName() const
	{
		return m_name;
	}

	const ActionType& Action::getType() const
	{
		return m_type;
	}

	void Action::setProperty(std::string property, float value)
	{
		m_properties.insert({property, value});
	}

	float Action::getProperty(std::string property)
	{
		return m_properties.find(property)->second;
	}

	bool Action::checkProperty(std::string property)
	{
		return m_properties.count(property) > 0;
	}

	Action::Action(Scenes::GameSceneActions name, ActionType type)
	{
		m_name = name;
		m_type = type;
	}

	Action::~Action()
	{

	}	
}

//template class Engine::Action<Scenes::GameSceneActions>;

//template class Engine::Action<Scenes::TitleSceneActions>;