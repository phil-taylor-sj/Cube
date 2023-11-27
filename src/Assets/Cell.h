#pragma once
#include <array>
#include "SpriteAsset.h"
#include "ISpriteAsset.h"

class Cell : public SpriteAsset, ISpriteAsset
{
public:
	void setTexture(const sf::Texture& texture) override;
	void updatePosition() override;
	void setCellIndices(int xCelIndex, int yCellIndex);
	sf::Vector2i getCellIndices();

	void setRotation(float angle) override;

	void setCellWidth(float cellWidth);

	Cell();
	virtual ~Cell();

protected:
	float _cellWidth;
	sf::Vector2f _nodePosition;
	sf::Vector2i _cellIndices;

};