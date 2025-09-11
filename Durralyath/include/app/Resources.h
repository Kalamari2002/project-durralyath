#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "config.h"
class Resources {
public:
	sf::Font regularTextFont;
	sf::Texture defaultPortrait;
	bool loadedRegularTextFont, loadedDefaultPortrait;

	Resources() {
		if (!(loadedRegularTextFont = regularTextFont.openFromFile(c_TEXT_FONT_PATH))) {
			std::cout << "ERROR: COULDN'T LOAD TEXT FONT" << std::endl;
		}

		if (!(loadedDefaultPortrait = defaultPortrait.loadFromFile(c_DEFAULT_PORTRAIT_PATH))) {
			std::cout << "ERROR: COULDN'T LOAD DEFAULT PORTRAIT FILE" << std::endl;
		}
	}
};