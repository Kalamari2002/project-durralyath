#include "interface/Clickable.h"
#include <iostream>
Clickable::Clickable(float xPos, float yPos, float width, float height) :
	xPos(xPos),
	yPos(yPos),
	width(width),
	height(height),
	hovered(false)
{}

void Clickable::onHoverEnter() {}
void Clickable::onHoverExit() {}

void Clickable::onMousePressed() {}
void Clickable::onMouseRelease() {}

void Clickable::setPosition(float xPos, float yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
}

void Clickable::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;
}


bool Clickable::isHovering(float xCursorPos, float yCursorsPos) {
	if (xCursorPos >= (this->xPos - (this->width / 2.0f)) && xCursorPos <= (this->xPos + (this->width / 2.0f)) &&
		yCursorsPos >= (this->yPos - (this->height / 2.0f)) && yCursorsPos <= (this->yPos + (this->height / 2.0f))) {
		if (!hovered) {
			onHoverEnter();
			hovered = true;
		}
		return true;
	}

	if (hovered) {
		onHoverExit();
		hovered = false;
	}

	return false;
}

void Clickable::draw(sf::RenderWindow& window) {

}