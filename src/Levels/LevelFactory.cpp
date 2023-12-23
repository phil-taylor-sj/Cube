#include "Levels/LevelFactory.h"

namespace Levels
{
	void LevelFactory::addTexture(const CellEntity& entity, CellGraphicsComponent& graphics)
	{
		if (entity.type = "Room")
			graphics.sprite.setTexture(
				Engine::TextureDict::getInstance()->getTexture(entity.subtype)
			);
		if (entity.type == "EdgeVoid")
		{
			graphics.sprite.setTexture(
				Engine::TextureDict::getInstance()->getTexture("EdgeVoid")
			);
			if (entity.subtype == "UpperEdge")
			{
				graphics.textureRotation = 180.f;
			}
			else if(entity.subtype == "LowerEdge")
			{
				graphics.textureRotation = 0.f;
			}
			else if (entity.subtpye == "LeftEdge")
			{
				graphics.textureRotation = 90.f;
			}
			else if (entity.subtype == "RightEdge")
			{
				graphics.textureRotation = 270.f;
			}
		}

		if (entity.type == "CornerVoid")
		{
			graphics.sprite.setTexture(
				Engine::TextureDict::getInstance()->getTexture("CornerVoid")
			);

			if (entity.subtype == "UpperLeft")
			{
				graphics.textureRotation = 90.f;
			}
			else if (entity.subtype == "UpperRight")
			{
				graphics.textureRotation = 180.f;
			}
			else if (entity.subtype == "LowerLeft")
			{
				graphics.textureRotation = 0.f;
			}
			else if (entity.subtype == "LowerRight")
			{
				graphics.textureRotation = 270.f;
			}
		}

		graphics.sprite.setRotation(graphics.textureRotation);

	}
}