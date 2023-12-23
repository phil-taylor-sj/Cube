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

namespace Engine
{
	class TextureDict
	{
	public:
		static TextureDict* getInstance();
		sf::Texture& getTexture(std::string name);
		void loadTexture(std::string name);
		void setExeFilepath( char* argv[]);
		void setRelativeFilepath(std::string relativePath);

	protected:
		TextureDict() = default;

	private:
		static TextureDict* _instance;
		std::map<std::string, sf::Texture> _textures;
		std::string _exePath = "./";
		std::string _relativePath = "./";

	};
}