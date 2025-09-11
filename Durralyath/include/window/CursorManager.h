#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class CursorManager {
private:
	sf::RenderWindow& window;
	bool hovering = false;
	sf::Cursor arrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
	sf::Cursor hand = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
public:
	CursorManager(sf::RenderWindow& window) : window(window){}

	void onHoveringEnter() {
		if (hovering) return;
		hovering = true;
		window.setMouseCursor(hand);
	}
	void onHoveringExit() {
		if (!hovering) return;
		hovering = false;
		window.setMouseCursor(arrow);
	}
};