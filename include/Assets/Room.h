#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Assets/Cell.h"
#include "Obstacles/StaticRectangle.h"

class Room : public Cell
{
public:
	void setTrapStatus(bool trapStatus);
	bool getTrapStatus();

	const std::map<std::string, std::shared_ptr<StaticRectangle>>
		getOuterWalls();

	Room();
	virtual ~Room();

protected:
	void _updateObstaclePositions() override;
	void _updateObstacleDimensions() override;

	std::map<std::string, std::shared_ptr<StaticRectangle>> _outerWalls;
	bool _isTrapped;
};

