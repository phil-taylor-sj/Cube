#pragma once

#include "Assets/FontDict.h"
#include <stdexcept>

namespace Assets
{
	FontDict* FontDict::m_instance = nullptr;

	FontDict* FontDict::getInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new FontDict;
		}
		return m_instance;
	}

	sf::Font& FontDict::getFont(std::string name)
	{
		if (m_fonts.find(name) == m_fonts.end())
		{
			throw std::invalid_argument(
				"Key '" + name + "' not found in m_fonts map of FontDict."
			);
		}

		return m_fonts[name];
	}

	void FontDict::loadFont(std::string name)
	{

		// Specify the relative path to your image file

		// Create the full path by concatenating the executable path and the relative image path
		m_fonts[name].loadFromFile(
			m_exePath + "/" + m_relativePath + "resources/fonts/" + name + ".png");
	}

	void FontDict::setExeFilepath(char* argv[])
	{
		std::filesystem::path exeFilepath = std::filesystem::canonical(
			std::filesystem::path(argv[0])
		).parent_path();
		m_exePath = exeFilepath.string();
	}

	void FontDict::setRelativeFilepath(std::string relativePath)
	{
		m_relativePath = relativePath;
	}
}