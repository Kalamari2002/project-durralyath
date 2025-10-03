#include "interface/EditableText.h"
#include <iostream>

EditableText::EditableText(std::string content, sf::Font& font, tgui::Gui& gui) :
	characterSize(30),
	content(content), 
	font(font),
	gui(gui),
	textDisplay(font, content),
	textColor(sf::Color::Black),
	textArea(tgui::EditBox::create()),
	clickable(0,0,0,0,*this),
	UInterface(0,0)
{
	textDisplay.setString(content);

	textDisplay.setPosition(sf::Vector2f(0, 0));
	textDisplay.setCharacterSize(characterSize);
	textDisplay.setFillColor(textColor);
	
	auto textBoundSize = textDisplay.getLocalBounds().size;
	setDimensions(textBoundSize.x, textBoundSize.y);

	textArea->setTextSize(characterSize);
	textArea->setWidth(TA_WIDTH);
	textArea->setHeight(height + TA_HEIGHT_MODIFIER);
	textArea->setPosition(xPos, yPos);
	textArea->setVisible(false);
	textArea->setMaximumCharacters(MAX_CHARACTER);
	textArea->setText(content);
	gui.add(textArea);

}

void EditableText::activate() {
	UInterface::activate();
	textArea->setVisible(true);
}

void EditableText::deactivate() {
	UInterface::deactivate();
	changeText(textArea->getText());
	textArea->setVisible(false);
}

void EditableText::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;
	clickable.setDimensions(this->width, this->height);
}

void EditableText::setPosition(float xPos, float yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
	textDisplay.setPosition(sf::Vector2f(this->xPos, this->yPos));

	float clYOffset = textDisplay.getLocalBounds().size.y;
	clickable.setPosition(this->xPos, this->yPos + clYOffset);
	
	float taXOffset = xCentralized ? textArea->getSize().x / 2.0f : 0.0f;
	float taYOffset = yCentralized ? textArea->getSize().y / 2.0f : 0.0f;
	textArea->setPosition(tgui::Vector2f(this->xPos - taXOffset, this->yPos - yCentralized));
}

void EditableText::setOrigin(float xOrigin, float yOrigin) {
	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	textDisplay.setOrigin(sf::Vector2f(xOrigin, yOrigin));
}

void EditableText::centralize(bool centralizeX, bool centralizeY) {
	std::cout << "centralized" << std::endl;
	const sf::FloatRect displayRect = textDisplay.getLocalBounds();
	float xCenter = centralizeX ? displayRect.size.x / 2.0f : xOrigin;
	float yCenter = centralizeY ? displayRect.size.y / 2.0f : yOrigin;
	setOrigin(xCenter, yCenter);

	xCentralized = centralizeX;
	yCentralized = centralizeY;
}

bool EditableText::onKeyPressed(sf::Keyboard::Scan scancode) {
	switch (scancode)
	{
	case sf::Keyboard::Scan::Enter:
		deactivate();
		return true;
	default:
		break;
	}
	return false;
}

bool EditableText::onClickAway() {
	deactivate();
	return true;
}

void EditableText::changeText(const tgui::String newText) {
	content = std::string(newText);
	textDisplay.setString(content);
	auto textBoundSize = textDisplay.getLocalBounds().size;
	setDimensions(textBoundSize.x, height);
	if (xCentralized || yCentralized) {
		centralize(xCentralized, yCentralized);
	}
}

void EditableText::draw(sf::RenderWindow& window) {
	if(!this->getIsActive())	// If current textbox is being edited, don't display text underneath
		window.draw(textDisplay);
}