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

class TextureDict
{
public:
	static TextureDict* getInstance();
	sf::Texture& getTexture(std::string name);
	void loadTexture(std::string name);
	void setFilepath( char* argv[]);

protected:
	TextureDict() = default;

private:
	static TextureDict* _instance;
	std::map<std::string, sf::Texture> _textures;
	std::string _exePath = "./";

};