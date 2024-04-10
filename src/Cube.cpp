#include <SFML/Graphics.hpp>
#include <string>

#include "Engine/GameEngine.h"
#include "Assets/TextureDict.h"
#include "Assets/FontDict.h"

int main(int argc, char* argv[])
{
	std::string relativePath = "../../../";

	Assets::TextureDict::getInstance()->setExeFilepath(argv);
	Assets::TextureDict::getInstance()->setRelativeFilepath(relativePath);

	Assets::FontDict::getInstance()->setExeFilepath(argv);
	Assets::FontDict::getInstance()->setRelativeFilepath(relativePath);

	Engine::GameEngine engine = Engine::GameEngine();
	engine.runEngine();

	return 0;
}