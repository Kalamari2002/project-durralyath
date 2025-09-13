#include "interface/Token.h"

Token::Token(float xPos, float yPos, float radius):
Clickable(xPos, yPos, radius * 2, radius * 2)
{
	portrait.setRadius(radius);
	portrait.setOrigin(sf::Vector2f(radius, radius));
	portrait.setPosition(sf::Vector2f(xPos, yPos));
	portrait.setFillColor(sf::Color::White);
}

void Token::setTexture(sf::Texture* texture) {
	portrait.setTexture(texture);
}

void Token::onHoverEnter(){
	portrait.setFillColor(sf::Color::Cyan);
}

void Token::onHoverExit(){
	portrait.setFillColor(sf::Color::White);
}

void Token::setPosition(float xPos, float yPos) {
	Clickable::setPosition(xPos, yPos);
	portrait.setPosition(sf::Vector2f(xPos, yPos));
}

void Token::draw(sf::RenderWindow& window) {
	window.draw(portrait);
}