#include "BoardElement.h"
BoardElement::BoardElement(float xPos, float yPos) : name("Entity"), xPos(xPos), yPos(yPos), cursor_xOffset(0.0f), cursor_yOffset(0.0f),
height(BASE_DIMENSION), width(BASE_DIMENSION), label(defaultFont, ""), hovered(false), held(false) {
	
	xOrigin = width / 2.0f;
	yOrigin = height / 2.0f;

	portrait = new sf::CircleShape(width / 2.0f);
	portrait->setOrigin(sf::Vector2f(xOrigin, yOrigin));
	portrait->setPosition(sf::Vector2f(xPos, yPos));

	labelYOffset = height / 2.0f + 30;

	label.setString(this->name);
	const sf::FloatRect labelRect = label.getLocalBounds();
	label.setOrigin(sf::Vector2f(labelRect.size.x / 2.0f, labelRect.size.y));
	label.setFillColor(sf::Color::Black);
	label.setPosition(sf::Vector2f(xPos, yPos + labelYOffset));
}
BoardElement::BoardElement(std::string name, float xPos, float yPos) : name(name), xPos(xPos), yPos(yPos), cursor_xOffset(0.0f), cursor_yOffset(0.0f),
height(BASE_DIMENSION), width(BASE_DIMENSION), label(defaultFont, ""), hovered(false), held(false) {
	xOrigin = width / 2.0f;
	yOrigin = height / 2.0f;

	portrait = new sf::CircleShape(width / 2.0f);
	portrait->setOrigin(sf::Vector2f(xOrigin, yOrigin));
	portrait->setPosition(sf::Vector2f(xPos, yPos));

	labelYOffset = height / 2.0f + 30;

	label.setString(this->name);
	const sf::FloatRect labelRect = label.getLocalBounds();
	label.setOrigin(sf::Vector2f(labelRect.size.x / 2.0f, labelRect.size.y));
	label.setFillColor(sf::Color::Black);
	label.setPosition(sf::Vector2f(xPos, yPos + labelYOffset));
}

bool BoardElement::isHovering(float cursor_xPos, float cursor_yPos) {
	if (cursor_xPos >= (this->xPos - (this->width / 2.0f)) && cursor_xPos <= (this->xPos + (this->width / 2.0f)) &&
		cursor_yPos >= (this->yPos - (this->height / 2.0f)) && cursor_yPos <= (this->yPos + (this->height / 2.0f))) {
		if (!hovered) {
			portrait->setFillColor(sf::Color::Green);
			hovered = true;
		}
		return true;
	}
	
	if(hovered){
		portrait->setFillColor(sf::Color::White);
		hovered = false;
	}

	return false;
}

void BoardElement::move(float xPos, float yPos){
	this->xPos = xPos;
	this->yPos = yPos;

	portrait->setPosition(sf::Vector2f(this->xPos, this->yPos));
	label.setPosition(sf::Vector2f(this->xPos, this->yPos + labelYOffset));
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

/**
* ??? QUESTION ???
* So about this, elements like textures, shapes and text all inherit form a "Drawable"
* class. I wonder which one's faster: passing a window reference as an argument so that
* every element can draw its own things OR making each element return a list of Drawable
* elements which the window can render on a "main" draw() method...
*/
void BoardElement::draw(sf::RenderWindow *window){
	window->draw(*portrait);
	window->draw(label);
}