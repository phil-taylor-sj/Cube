#pragma once
#include <string>
#include <map>
#include "Scenes/GameSceneActions.h"
#include "Scenes/TitleSceneActions.h"

namespace Engine
{
	enum ActionType
	{
		NONE, 
		PRESS,
		RELEASE
	};

	class Action
	{
	public:
		const Scenes::GameSceneActions& getName() const;
		const ActionType& getType() const;

		void setProperty(std::string property, float value);
		float getProperty(std::string property);
		bool checkProperty(std::string property);

		Action(Scenes::GameSceneActions name, ActionType type);
		~Action();
	
	private:
		Scenes::GameSceneActions m_name;
		ActionType m_type;
		std::map<std::string, float> m_properties;
	};
}

