#include "board/BoardElement.h"
BoardElement::BoardElement(unsigned int id, float xPos, float yPos, 
	InterfaceManager& interfaceManager, Resources& resources, tgui::Gui& gui) :
	name("Entity"),
	id(id),
	xPos(xPos), yPos(yPos), 
	cursor_xOffset(0.0f), cursor_yOffset(0.0f),
	height(BASE_DIMENSION), width(BASE_DIMENSION),
	interfaceManager(interfaceManager),
	gui(gui),
	nameTag(name, resources.regularTextFont, gui),
	token(xPos,yPos,height/2.0f),
	hovered(false), 
	held(false)
{
	
	xOrigin = width / 2.0f;
	yOrigin = height / 2.0f;

	if (resources.loadedDefaultPortrait) {
		token.setTexture(&resources.defaultPortrait);
	}

	labelYOffset = height / 2.0f;
	nameTag.centralize(true, false);
	nameTag.setPosition(this->xPos, this->yPos + labelYOffset);
	interfaceManager.subscribe(&nameTag);

}
BoardElement::BoardElement(unsigned int id, std::string name, float xPos, float yPos, 
	InterfaceManager& interfaceManager, Resources& resources, tgui::Gui& gui) :
	id(id),
	name(name), 
	xPos(xPos), yPos(yPos), 
	cursor_xOffset(0.0f), cursor_yOffset(0.0f),
	height(BASE_DIMENSION), width(BASE_DIMENSION),
	interfaceManager(interfaceManager),
	gui(gui),
	nameTag(name, resources.regularTextFont, gui),
	token(xPos, yPos, height / 2.0f),
	hovered(false),
	held(false)
{
	xOrigin = width / 2.0f;
	yOrigin = height / 2.0f;

	
	if (resources.loadedDefaultPortrait) {
		token.setTexture(&resources.defaultPortrait);
	}

	labelYOffset = height / 2.0f;
	nameTag.centralize(true, false);
	nameTag.setPosition(this->xPos, this->yPos + labelYOffset);
	interfaceManager.subscribe(&nameTag);
}

bool BoardElement::isHovering(float cursor_xPos, float cursor_yPos) {
	return token.isHovering(cursor_xPos, cursor_yPos) || nameTag.clickable.isHovering(cursor_xPos, cursor_yPos);
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
}

void BoardElement::draw(sf::RenderWindow& window){
	token.draw(window);
	nameTag.draw(window);
}

sf::Vector2f BoardElement::getPosition() {
	return sf::Vector2f(this->xPos, this->yPos);
}

unsigned int BoardElement::getId() {
	return id;
}