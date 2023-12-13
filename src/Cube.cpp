#include <SFML/Graphics.hpp>
#include <string>

#include "Engine/GameEngine.h"
#include "Engine/TextureDict.h"

int main(int argc, char* argv[])
{
	std::string relativePath = "../../../";

	TextureDict::getInstance()->setExeFilepath(argv);
	TextureDict::getInstance()->setRelativeFilepath(relativePath);

	GameEngine engine = GameEngine();
	engine.runEngine();

	return 0;
}