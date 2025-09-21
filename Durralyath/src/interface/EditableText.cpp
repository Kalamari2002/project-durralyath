#include "interface/EditableText.h"

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
	
	ta_xOffset = (TA_WIDTH) / 2;
	ta_yOffset = textBoundSize.y / 2 + TA_HEIGHT_MODIFIER;
	textArea->setWidth(TA_WIDTH);
	textArea->setHeight(height + TA_HEIGHT_MODIFIER);
	textArea->setPosition(xPos - ta_xOffset, yPos - ta_yOffset);
	textArea->setTextSize(characterSize);
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
	clickable.setPosition(this->xPos, this->yPos);
	textDisplay.setPosition(sf::Vector2f(this->xPos, this->yPos));
	textArea->setPosition(tgui::Vector2f(this->xPos - ta_xOffset, this->yPos - ta_yOffset));
}

void EditableText::setOrigin(float xOrigin, float yOrigin) {
	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	textDisplay.setOrigin(sf::Vector2f(xOrigin, yOrigin));
}

void EditableText::centralize() {
	const sf::FloatRect displayRect = textDisplay.getLocalBounds();
	setOrigin(displayRect.size.x / 2.0f, displayRect.size.y);
}

bool EditableText::onClickAway() {
	deactivate();
	return true;
}

void EditableText::changeText(const tgui::String newText) {
	content = std::string(newText);
	textDisplay.setString(content);
	auto textBoundSize = textDisplay.getLocalBounds().size;
	setDimensions(textBoundSize.x, textBoundSize.y);
}

void EditableText::draw(sf::RenderWindow& window) {
	window.draw(textDisplay);
}