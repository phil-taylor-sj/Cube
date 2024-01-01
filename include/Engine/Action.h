#pragma once
#include <string>
#include <map>
#include "Scenes/GameSceneActions.h"

namespace Engine
{
	enum ActionType
	{
		PRESS = 0,
		RELEASE = 1
	};

	template <typename T>
	class Action
	{
	public:
		const T& getName() const;
		const ActionType& getType() const;

		Action(T name, ActionType type);
		~Action();
	
	private:
		T m_name;
		ActionType m_type;
	};
}

