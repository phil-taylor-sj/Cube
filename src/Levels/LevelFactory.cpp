#include "Levels/LevelFactory.h"

namespace Levels
{
	void LevelFactory::addTexture(const CellEntity& entity, CellGraphicsComponent& graphics)
	{
		std::map<std::string, float> voidConfig;
		voidConfig.insert({"UpperEdge", 180.f});
		voidConfig.insert({"LowerEdge", 0.f });
		voidConfig.insert({"LeftEdge", 90.f });
		voidConfig.insert({"RightEdge", 270.f});
		voidConfig.insert({"UpperLeft", 90.f });
		voidConfig.insert({"UpperRight", 180.f });
		voidConfig.insert({"LowerLeft", 0.f });
		voidConfig.insert({"LowerRight", 270.f });


		if (entity.type == "Room")
		{
			graphics.sprite.setTexture(
				Engine::TextureDict::getInstance()->getTexture(entity.subtype)
			);
		}

		if (voidConfig.count(entity.subtype) > 0)
		{
			graphics.sprite.setTexture(
				Engine::TextureDict::getInstance()->getTexture(entity.type)
			);
			graphics.textureRotation = voidConfig.find(entity.subtype);
			graphics.sprite.setRotation(graphics.textureRotation);
		}
	}
}