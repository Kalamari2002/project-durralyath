#pragma once
#include <string>
#include <vector>
#include "window/CursorManager.h"
#include "board/BoardElement.h"
#include <SFML/Graphics.hpp>

class Board
{
private:
	std::vector<BoardElement*> elements;
	BoardElement* selectedElement;
	BoardElement* hoveredElement;
	unsigned int id;
	enum USER_TOOLS { CURSOR, MOVE, ADD_ELEMENT };
	USER_TOOLS activeTool;
public:
	std::string name;
public:
	Board(std::string name);
	Board(std::string name, unsigned int id);
	~Board();

	void onLeftMousePressed(float xPos, float yPos);
	void onLeftMouseReleased();

	void onRightMousePressed();
	void onRightMouseReleased();

	void onMouseMove(float xPos, float yPos, CursorManager *cursor);

	void drawElements(sf::RenderWindow *window);
};

