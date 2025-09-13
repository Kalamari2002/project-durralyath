#include "interface/EditableText.h"

EditableText::EditableText(std::string content, sf::Font& font, tgui::Gui& gui, bool isCentrlized) :
	Clickable(0, 0, 1, 1),
	characterSize(30),
	content(content), 
	font(font),
	textDisplay(font, content),
	textColor(sf::Color::Black),
	textArea(tgui::TextArea::create())
{
	textDisplay.setString(content);
	textDisplay.setPosition(sf::Vector2f(xPos, yPos));
	textDisplay.setCharacterSize(characterSize);
	textDisplay.setFillColor(textColor);

	if (isCentrlized) centralize();
	
	auto textBoundSize = textDisplay.getLocalBounds().size;
	Clickable::setDimensions(textBoundSize.x, textBoundSize.y);

	ta_xOffset = (textBoundSize.x + TA_WIDTH_MODIFIER) / 2;
	ta_yOffset = textBoundSize.y / 2 + TA_HEIGHT_MODIFIER;
	textArea->setWidth(width + TA_WIDTH_MODIFIER);
	textArea->setHeight(height + TA_HEIGHT_MODIFIER);
	textArea->setPosition(xPos - ta_xOffset, yPos - ta_yOffset);
	textArea->setVisible(false);
	gui.add(textArea);
}

EditableText::EditableText(std::string content, sf::Font& font, sf::Color textColor, tgui::Gui& gui, bool isCentrlized) :
	Clickable(0, 0, 1, 1),
	characterSize(30),
	content(content),
	font(font),
	textDisplay(font, content),
	textColor(textColor),
	textArea(tgui::TextArea::create())
{
	textDisplay.setString(content);
	textDisplay.setPosition(sf::Vector2f(xPos, yPos));
	textDisplay.setCharacterSize(characterSize);
	textDisplay.setFillColor(textColor);

	if (isCentrlized) centralize();

	auto textBoundSize = textDisplay.getLocalBounds().size;
	Clickable::setDimensions(textBoundSize.x, textBoundSize.y);

	ta_xOffset = textBoundSize.x / 2 + TA_WIDTH_MODIFIER;
	ta_yOffset = textBoundSize.y / 2 + TA_HEIGHT_MODIFIER;
	textArea->setWidth(width + TA_WIDTH_MODIFIER);
	textArea->setHeight(height + TA_HEIGHT_MODIFIER);
	textArea->setPosition(xPos - ta_xOffset, yPos - ta_yOffset);
	textArea->setVisible(false);
	gui.add(textArea);
}

void EditableText::setPosition(float xPos, float yPos) {
	Clickable::setPosition(xPos, yPos);
	textDisplay.setPosition(sf::Vector2f(this->xPos, this->yPos));
	textArea->setPosition(tgui::Vector2f(this->xPos - ta_xOffset, this->yPos - ta_yOffset));
}

void EditableText::setOrigin(float xOrigin, float yOrigin) {
	textDisplay.setOrigin(sf::Vector2f(xOrigin, yOrigin));
}

void EditableText::onMousePressed() {
	textArea->setVisible(true);
}

void EditableText::centralize() {
	const sf::FloatRect displayRect = textDisplay.getLocalBounds();
	textDisplay.setOrigin(sf::Vector2f(displayRect.size.x / 2.0f, displayRect.size.y));
}


void EditableText::draw(sf::RenderWindow& window) {
	window.draw(textDisplay);
}