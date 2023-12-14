#include "Assets/Cell.h"
#include <iostream>

void Cell::setTexture(const sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_sprite.setOrigin(
		_sprite.getLocalBounds().width * 0.5f,
		_sprite.getLocalBounds().height * 0.5f
	);
	if (_sprite.getLocalBounds().width != _cellWidth)
	{
		_sprite.scale(
				_cellWidth / _sprite.getLocalBounds().width,
				_cellWidth / _sprite.getLocalBounds().height
		);
	}
}


void Cell::updatePosition()
{
	_nodePosition.x = _cellWidth * _cellIndices.x;
	_nodePosition.y = _cellWidth * _cellIndices.y;
	_position.x = _nodePosition.x + 0.5f * _cellWidth;
	_position.y = _nodePosition.y + 0.5f * _cellWidth;
	_updateObstaclePositions();
	_sprite.setPosition(_position);
}

sf::Vector2i Cell::getCellIndices()
{
	return _cellIndices;
}

void Cell::setCellIndices(int xCellIndex, int yCellIndex)
{
	_cellIndices.x = xCellIndex;
	_cellIndices.y = yCellIndex;
}

void Cell::setRotation(float angle)
{
	_sprite.setRotation(angle);
}

void Cell::setCellWidth(float cellWidth)
{
	_cellWidth = cellWidth;
	_updateObstaclePositions();
	_updateObstacleDimensions();
}

Cell::Cell() 
{
	_cellWidth = 512.f;
	_cellIndices.x = 0;
	_cellIndices.y = 0;
	_nodePosition.x = 0.f;
	_nodePosition.y = 0.f;
}

Cell::~Cell()
{

}

void Cell::_updateObstaclePositions()
{
}


void Cell::_updateObstacleDimensions()
{
}