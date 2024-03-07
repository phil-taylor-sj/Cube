/*
Class: TextureDict [Singleton Pattern]

Inheritence: None

Description:
	- 

Methods:
	getInstance();	

*/

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <filesystem>

namespace Assets
{
	class TextureDict
	{
	public:
		static TextureDict* getInstance();
		sf::Texture& getTexture(std::string name);
		void loadTexture(std::string name);
		void setExeFilepath( char* argv[]);
		void setRelativeFilepath(std::string relativePath);
		void setRepeated(std::string name, bool isRepeated);

	protected:
		TextureDict() = default;

	private:
		static TextureDict* m_instance;
		std::map<std::string, sf::Texture> m_textures;
		std::string m_exePath = "./";
		std::string m_relativePath = "./";

	};
}