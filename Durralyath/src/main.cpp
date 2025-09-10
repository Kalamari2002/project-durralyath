#pragma once
#include "board/Board.h"
#include "window/CursorManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Config.hpp>
#include<SFML/Window/Cursor.hpp>
#include<SFML/Window/Event.hpp>

const int windowWidth = 1600;
const int windowHeight = 900;

sf::Color defaultFillColor(168,135,30);

int main() {
	sf::RenderWindow window(sf::VideoMode({ windowWidth,windowHeight }), "Durralyath");
	CursorManager* cursorManager = new CursorManager(&window);
	Board* board = new Board("Campaign");
	
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) window.close();
			float xPos = sf::Mouse::getPosition(window).x;
			float yPos = sf::Mouse::getPosition(window).y;
			if (event->is<sf::Event::MouseMoved>()) {
				board->onMouseMove(xPos, yPos, cursorManager);
			}
			if (event->is<sf::Event::MouseButtonPressed>()) {
				if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
					board->onLeftMousePressed(xPos, yPos);
				}
				if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right) {
					board->onRightMousePressed();
				}
			}
			if (event->is<sf::Event::MouseButtonReleased>()) {
				if (event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left) {
					board->onLeftMouseReleased();
				}
				
			}
		}
		window.clear(defaultFillColor);
		board->drawElements(&window);
		window.display();
	}
	return 0;
}