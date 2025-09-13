#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <string>
#include "interface/Clickable.h"
class EditableText : public Clickable
{
private:
	sf::Font& font;
	sf::Text textDisplay;
	sf::Color textColor;
	tgui::TextArea::Ptr textArea;
	std::string content;
	unsigned int characterSize;
	float ta_xOffset = 0;
	float ta_yOffset = 0;
	const float TA_HEIGHT_MODIFIER = 10.0f;
	const float TA_WIDTH_MODIFIER = 10.0f;

public:
	EditableText(std::string content, sf::Font& font, tgui::Gui& gui, bool isCentralized = false);
	EditableText(std::string content, sf::Font& font, sf::Color textColor, tgui::Gui& gui, bool isCrentrlized = false);

	void setPosition(float xPos, float yPos) override;
	void setOrigin(float xOrigin, float yOrigin);
	void onMousePressed() override;
	void centralize();
	void draw(sf::RenderWindow& window) override;
};

