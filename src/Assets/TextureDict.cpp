#include "Assets/TextureDict.h"
#include <stdexcept>

namespace Assets
{
	TextureDict* TextureDict::m_instance = nullptr;

	TextureDict* TextureDict::getInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new TextureDict;
		}
		return m_instance;
	}

	sf::Texture& TextureDict::getTexture(std::string name)
	{
		if (m_textures.find(name) == m_textures.end())
		{
			throw std::invalid_argument(
				"Key '" + name + "' not found in _textures map of TextureDict."
			);
		}

		return m_textures[name];
	}

	void TextureDict::loadTexture(std::string name)
	{

		// Specify the relative path to your image file
   
		// Create the full path by concatenating the executable path and the relative image path
		m_textures[name].loadFromFile(
			m_exePath + "/" + m_relativePath + "resources/graphics/" + name + ".png");
	}

	void TextureDict::setExeFilepath(char* argv[])
	{
		std::filesystem::path exeFilepath = std::filesystem::canonical(
				std::filesystem::path(argv[0])
				).parent_path();
		m_exePath = exeFilepath.string();
	}

	void TextureDict::setRepeated(std::string name, bool isRepeated)
	{
		if (m_textures.find(name) == m_textures.end())
		{
			throw std::invalid_argument(
				"Key '" + name + "' not found in _textures map of TextureDict."
			);
		}

		m_textures[name].setRepeated(isRepeated);
	}

	void TextureDict::setRelativeFilepath(std::string relativePath)
	{
		m_relativePath = relativePath;
	}
}