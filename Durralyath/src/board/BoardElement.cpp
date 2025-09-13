#include "board/BoardElement.h"
BoardElement::BoardElement(float xPos, float yPos, Resources& resources, tgui::Gui& gui) :
	name("Entity"), 
	xPos(xPos), yPos(yPos), 
	cursor_xOffset(0.0f), cursor_yOffset(0.0f),
	height(BASE_DIMENSION), width(BASE_DIMENSION),
	gui(gui),
	nameTag(name, resources.regularTextFont, gui, true),
	token(xPos,yPos,height/2.0f),
	hovered(false), 
	held(false)
{
	
	xOrigin = width / 2.0f;
	yOrigin = height / 2.0f;

	if (resources.loadedDefaultPortrait) {
		token.setTexture(&resources.defaultPortrait);
	}

	labelYOffset = height / 2.0f + 30;
	nameTag.setPosition(this->xPos, this->yPos + labelYOffset);
}
BoardElement::BoardElement(std::string name, float xPos, float yPos, Resources& resources, tgui::Gui& gui) :
	name(name), 
	xPos(xPos), yPos(yPos), 
	cursor_xOffset(0.0f), cursor_yOffset(0.0f),
	height(BASE_DIMENSION), width(BASE_DIMENSION),
	gui(gui),
	nameTag(name, resources.regularTextFont, gui, true),
	token(xPos, yPos, height / 2.0f),
	hovered(false),
	held(false)
{
	xOrigin = width / 2.0f;
	yOrigin = height / 2.0f;

	
	if (resources.loadedDefaultPortrait) {
		token.setTexture(&resources.defaultPortrait);
	}

	labelYOffset = height / 2.0f + 30;
	nameTag.setPosition(this->xPos, this->yPos + labelYOffset);
}

bool BoardElement::isHovering(float cursor_xPos, float cursor_yPos) {
	return token.isHovering(cursor_xPos, cursor_yPos) || nameTag.isHovering(cursor_xPos, cursor_yPos);
}

void BoardElement::move(float xPos, float yPos){
	this->xPos = xPos;
	this->yPos = yPos;

	token.setPosition(this->xPos, this->yPos);
	nameTag.setPosition(this->xPos, this->yPos + labelYOffset);
}

void BoardElement::hold(float cursor_xPos, float cursor_yPos) {
	if (held) return;

	held = true;
	cursor_xOffset = xPos - cursor_xPos;
	cursor_yOffset = yPos - cursor_yPos;
}

void BoardElement::release() {
	held = false;
}

void BoardElement::drag(float cursor_xPos, float cursor_yPos) {
	float newXPos = cursor_xOffset + cursor_xPos;
	float newYPos = cursor_yOffset + cursor_yPos;

	move(newXPos, newYPos);
}

void BoardElement::onMousePressed(float cursor_xPos, float cursor_yPos) {
	if (token.isHovering(cursor_xPos, cursor_yPos)) {
		hold(cursor_xPos, cursor_yPos);
	}
	else if (nameTag.isHovering(cursor_xPos, cursor_yPos)) {
		nameTag.onMousePressed();
	}
}

void BoardElement::draw(sf::RenderWindow& window){
	token.draw(window);
	nameTag.draw(window);
}