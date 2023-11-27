#include  "Room.h"

Room::Room()
{

}

Room::~Room()
{

}

void Room::setTrapStatus(bool trapStatus)
{
	_isTrapped = trapStatus;
}

bool Room::getTrapStatus()
{
	return _isTrapped;
}