#pragma once
#include "Entity.h"
#include "BoardElement.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Config.hpp>
#include<SFML/Window/Cursor.hpp>
#include<SFML/Window/Event.hpp>

const int windowWidth = 1600;
const int windowHeight = 900;

sf::Color defaultFillColor(168,135,30);

int main() {
	sf::RenderWindow window(sf::VideoMode({ windowWidth,windowHeight }), "Its Alive!");
	sf::CircleShape shape(100.f);
	auto arrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
	auto hand = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
	BoardElement *bE = new BoardElement("Character", 100, 100);
	shape.setFillColor(sf::Color::Green);
	bool hovering = false;
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) window.close();
			float xPos = sf::Mouse::getPosition(window).x;
			float yPos = sf::Mouse::getPosition(window).y;
			if (event->is<sf::Event::MouseMoved>()) {
				if (bE->isHovering(xPos, yPos)) {
					if (!hovering) {
						hovering = true;
						window.setMouseCursor(hand);
					}
				}
				else {
					if (hovering) {
						hovering = false;
						window.setMouseCursor(arrow);
					}
				}
				if (bE->held) {
					bE->drag(xPos, yPos);
				}
				std::cout << xPos << ", " << yPos << std::endl;
			}
			if (event->is<sf::Event::MouseButtonPressed>()) {
				if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
					if (bE->isHovering(xPos, yPos)) {
						bE->hold(xPos, yPos);
					}
				}
			}
			if (event->is<sf::Event::MouseButtonReleased>()) {
				if (event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left) {
					if (bE->held) bE->release();
				}
			}
		}
		window.clear(defaultFillColor);
		bE->draw(&window);
		window.display();
	}
	//Entity* entity = new Entity();
	return 0;
}