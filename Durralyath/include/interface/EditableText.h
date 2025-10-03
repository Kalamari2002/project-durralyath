#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <string>
#include "interface/UInterface.h"
#include "interface/OpenInterfaceClickable.h"
class EditableText : public UInterface
{
private:
	sf::Font& font;
	sf::Text textDisplay;
	sf::Color textColor;
	tgui::Gui& gui;
	tgui::EditBox::Ptr textArea;
	std::string content;
	unsigned int characterSize;

	const float TA_HEIGHT_MODIFIER = 10.0f; // This will vary among different children
	const float TA_WIDTH_MODIFIER = 10.0f; // same here
	const float TA_WIDTH = 400.0f;  // same here
	const unsigned int MAX_CHARACTER = 20; // same here

	bool xCentralized = false;
	bool yCentralized = false;
private:
	void changeText(const tgui::String newText);
public:
	OpenInterfaceClickable clickable;
public:
	EditableText(std::string content, sf::Font& font, tgui::Gui& gui);
	
	void activate() override;
	void deactivate() override;
	void centralize(bool centralizeX=true, bool centralizeY=true) override;
	void setDimensions(float width, float height) override;
	void setPosition(float xPos, float yPos) override;
	void setOrigin(float xOrigin, float yOrigin) override;

	bool onKeyPressed(sf::Keyboard::Scan scancode) override;
	bool onClickAway() override;
	
	void draw(sf::RenderWindow& window) override;
};

