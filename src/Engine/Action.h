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
		const Scenes::SceneActions& getName() const;
		const ActionType& getType() const;

		void setProperty(std::string property, float value);
		float getProperty(std::string property);
		bool checkProperty(std::string property);

		Action(Scenes::SceneActions name, ActionType type);
		~Action();
	
	private:
		Scenes::SceneActions m_name;
		ActionType m_type;
		std::map<std::string, float> m_properties;
	};
}

