#include <SFML/Graphics.hpp>
#include "./Engine/GameEngine.h"
#include "./Engine/TextureDict.h"

int main(int argc, char* argv[])
{
	TextureDict::getInstance()->setFilepath(argv);
	GameEngine engine = GameEngine();
	engine.runEngine();

	return 0;
}