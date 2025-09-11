#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/**
* Responsible for changing the cursor when needed. It's passed as a reference
* to other objects.
*/
class CursorManager {
private:
	sf::RenderWindow& window;
	bool hovering = false;
	sf::Cursor arrow = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
	sf::Cursor hand = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
public:
	CursorManager(sf::RenderWindow& window) : window(window){}

	/**
	* Called when the cursor is hovering over something that's clickable.
	*/
	void onHoveringEnter() {
		if (hovering) return;
		hovering = true;
		window.setMouseCursor(hand);
	}

	/**
	* Called when the cursor exits an object that's clickable.
	*/
	void onHoveringExit() {
		if (!hovering) return;
		hovering = false;
		window.setMouseCursor(arrow);
	}
};