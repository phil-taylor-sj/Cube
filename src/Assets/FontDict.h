/*
Class: FontDict [Singleton Pattern]

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
	class FontDict
	{
	public:
		static FontDict* getInstance();
		sf::Font& getFont(std::string name);
		void loadFont(std::string name);
		void setExeFilepath(char* argv[]);
		void setRelativeFilepath(std::string relativePath);

	protected:
		FontDict() = default;

	private:
		static FontDict* m_instance;
		std::map<std::string, sf::Font> m_fonts;
		std::string m_exePath = "./";
		std::string m_relativePath = "./";

	};
}