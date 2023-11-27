#include "TextureDict.h"
#include <stdexcept>


TextureDict* TextureDict::_instance = nullptr;

TextureDict* TextureDict::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TextureDict;
	}
	return _instance;
}

sf::Texture& TextureDict::getTexture(std::string name)
{
	if (_textures.find(name) == _textures.end())
	{
		throw std::invalid_argument(
			"Key '" + name + "' not found in _textures map of TextureDict."
		);
	}

	return _textures[name];
}

void TextureDict::loadTexture(std::string name)
{
	 
		
    // Specify the relative path to your image file
   

    // Create the full path by concatenating the executable path and the relative image path
	_textures[name].loadFromFile(
		_exePath + "/../Resources/Graphics/" + name + ".png");
}

void TextureDict::setFilepath(char* argv[])
{
	std::filesystem::path exeFilepath = std::filesystem::canonical(
			std::filesystem::path(argv[0])
			).parent_path();
	_exePath = exeFilepath.string();
	
}