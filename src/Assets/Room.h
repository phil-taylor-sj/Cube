#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Room : public Cell
{
public:
	void setTrapStatus(bool trapStatus);
	bool getTrapStatus();

	Room();
	virtual ~Room();

private:
	bool _isTrapped;
};

