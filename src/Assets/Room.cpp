#include  "Assets/Room.h"

void Room::setTrapStatus(bool trapStatus)
{
	_isTrapped = trapStatus;
}

bool Room::getTrapStatus()
{
	return _isTrapped;
}

const std::map<std::string, std::shared_ptr<StaticRectangle>> 
	Room::getOuterWalls()
{
	return _outerWalls;
}

Room::Room()
{
	_isTrapped = false;
	
	// Initialise the eight outer walls
	float wallLength = 0.34375;
	float wallDepth = 0.078125;
	float wallHalfLength = 0.5f * wallLength;
	float wallHalfDepth = 0.5f * wallDepth;

	float wallPositions[8][2] = {
		{wallHalfDepth,  wallHalfLength},
		{wallHalfDepth, 1.f - wallHalfLength},
		{1.f - wallHalfDepth, wallHalfLength},
		{1.f - wallHalfDepth, 1.f - wallHalfLength},
		{wallHalfLength,  wallHalfDepth},
		{wallHalfLength, 1.f - wallHalfDepth},
		{1.f - wallHalfLength, wallHalfDepth},
		{1.f - wallHalfLength, 1.f - wallHalfDepth}
	};

	std::array<std::string, 8> wallKeys = {
		"wallLeft1", "wallLeft2", 
		"wallRight1", "wallRight2", 
		"wallUpper1", "wallLower1", 
		"wallUpper2", "wallLower2"
	};

	for (int i = 0; i <= 3; i++)
	{
		_outerWalls[wallKeys[i]] = std::make_shared<StaticRectangle>();
		_outerWalls[wallKeys[i]]->setRelativeDimensions(wallDepth, wallLength);
		_outerWalls[wallKeys[i]]->setRelativePosition(
			wallPositions[i][0], wallPositions[i][1]
			);
	}
	for (int i = 4; i <= 7; i++)
	{
		_outerWalls[wallKeys[i]] = std::make_shared<StaticRectangle>();
		_outerWalls[wallKeys[i]]->setRelativeDimensions(wallLength, wallDepth);
		_outerWalls[wallKeys[i]]->setRelativePosition(
			wallPositions[i][0], wallPositions[i][1]
		);
	}
}

Room::~Room()
{

}

void Room::_updateObstaclePositions()
{
	for (std::pair<const std::string, std::shared_ptr<StaticRectangle>> 
		entry : _outerWalls)
	{
		entry.second->setCellPosition(_nodePosition);
	}
}

void Room::_updateObstacleDimensions()
{
	for (std::pair<const std::string, std::shared_ptr<StaticRectangle>>
			entry : _outerWalls)
		{
			entry.second->setCellWidth(_cellWidth);
		}
}