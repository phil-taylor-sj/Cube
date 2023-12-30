#include <SFML/Graphics.hpp>
#include <string>

#include "Engine/GameEngine.h"
#include "Assets/TextureDict.h"

int main(int argc, char* argv[])
{
	std::string relativePath = "../../../";

	Assets::TextureDict::getInstance()->setExeFilepath(argv);
	Assets::TextureDict::getInstance()->setRelativeFilepath(relativePath);

	Engine::GameEngine engine = Engine::GameEngine();
	engine.runEngine();

	return 0;
}