#include "Actors/ActorFactory.h"

namespace Actors
{
	void ActorFactory::buildGraphicsComponent(
		const ActorTypeComponent& types, ActorGraphicsComponent& graphics
	)
	{
		std::string textureName;
		switch (types.type)
		{
			case ActorTypes::PLAYER:
				textureName = "PlayerPlaceholder";
				break;
			default:
				return;
		}

		graphics.sprite.setTexture(
			Assets::TextureDict::getInstance()->getTexture("PlayerPlaceholder")
		);

		graphics.sprite.setOrigin(
			graphics.sprite.getLocalBounds().width,
			graphics.sprite.getLocalBounds().height
		);
	}
}