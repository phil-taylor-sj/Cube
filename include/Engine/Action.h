#pragma once
#include <string>
#include <map>
#include "Scenes/GameSceneActions.h"

namespace Engine
{
	enum ActionType
	{
		NONE, 
		PRESS,
		RELEASE
	};

	template <typename T>
	class Action
	{
	public:
		const T& getName() const;
		const ActionType& getType() const;

		void setProperty(std::string property, float value);
		float getProperty(std::string property);
		bool checkProperty(std::string property);

		Action(T name, ActionType type);
		~Action();
	
	private:
		T m_name;
		ActionType m_type;
		std::map<std::string, float> m_properties;
	};
}

