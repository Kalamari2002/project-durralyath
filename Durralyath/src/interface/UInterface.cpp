#include "interface/UInterface.h"

UInterface::UInterface(float xPos, float yPos, bool isVisible) :
	xPos(xPos), yPos(yPos),
	xOrigin(0), yOrigin(0),
	width(0), height(0),
	isVisible(isVisible),
	isActive(false),
	frame(sf::RectangleShape(sf::Vector2f(width, height)))
{
	frame.setFillColor(c_DEFAULT_WINDOW_BACKGROUND);
}

UInterface::UInterface(float xPos, float yPos, float width, float height, bool isVisible) :
	xPos(xPos), yPos(yPos),
	xOrigin(0), yOrigin(0),
	width(width), height(height), 
	isVisible(isVisible),
	isActive(false),
	frame(sf::RectangleShape(sf::Vector2f(width, height)))
{
	frame.setFillColor(c_DEFAULT_WINDOW_BACKGROUND);
}

void UInterface::activate() {
	isActive = true;
	//interfaceManager.switchInterface(this);
}

void UInterface::deactivate() {
	isActive = false;
}

void UInterface::setPosition(float xPos, float yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
	frame.setPosition(sf::Vector2f(this->xPos, this->yPos));
}

void UInterface::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;

	frame.setSize(sf::Vector2f(this->width, this->height));
}

void UInterface::centralize() {
	float xCenter = width / 2.0f;
	float yCenter = height / 2.0f;
	setOrigin(xCenter, yCenter);
}

void UInterface::setOrigin(float xOrigin, float yOrigin) {
	this->xOrigin = xOrigin;
	this->yOrigin = yOrigin;
	frame.setOrigin(sf::Vector2f(this->xOrigin, this->yOrigin));
}


void UInterface::draw(sf::RenderWindow& window) {
	if (!isVisible) return;
	window.draw(frame);
}

void UInterface::setIsVisible(bool isVisible) {
	this->isVisible = isVisible;
}

bool UInterface::getIsActive() {
	return isActive;
}

bool UInterface::isWithinBounds(float cursor_xPos, float cursor_yPos) {
	float topCornerX = xPos - xOrigin;
	float topCornerY = yPos - yOrigin;
	return (
		cursor_xPos >= topCornerX && cursor_xPos <= topCornerX + width &&
		cursor_yPos >= topCornerY && cursor_yPos <= topCornerY + height
	);
}

bool UInterface::onClickAway() {
	return true;
}