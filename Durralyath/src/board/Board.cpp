#include "board/Board.h"
#include <iostream>

Board::Board(std::string name, Resources& resources, InterfaceManager& interfaceManager, tgui::Gui& gui) : 
	name(name), 
	id(0), 
	resources(resources),
	interfaceManager(interfaceManager),
	gui(gui),
	edgeManager(resources, gui)
{
	activeTool = USER_TOOLS::MOVE;
	selectedElement = nullptr;
	hoveredElement = nullptr;
	BoardElement* newEl = new BoardElement(idCount++, "Character", 0, 0, resources, gui);
	elements.push_back(newEl);
}

Board::Board(std::string name, unsigned int id, Resources& resources, InterfaceManager& interfaceManager, tgui::Gui& gui) : 
	name(name), 
	id(id), 
	resources(resources),
	interfaceManager(interfaceManager),
	gui(gui),
	edgeManager(resources, gui)
{
	activeTool = USER_TOOLS::MOVE;
	selectedElement = nullptr;
	hoveredElement = nullptr;
	BoardElement* newEl = new BoardElement(idCount++, "Character", 0, 0, resources,gui);
	elements.push_back(newEl);
}

Board::~Board() {
	selectedElement = nullptr;
	hoveredElement = nullptr;

	for (BoardElement* el : elements) {
		delete el;
	}

	std::cout << "Deleted elements" << std::endl;
}

void Board::onLeftMousePressed(float xPos, float yPos) {
	std::cout << "Left Pressed on Board" << std::endl;
	switch (activeTool) {
	case USER_TOOLS::MOVE:
		interfaceManager.onMousePress(xPos, yPos);
		if (hoveredElement != nullptr) {
			selectedElement = hoveredElement;
			selectedElement->onMousePressed(xPos, yPos, interfaceManager);
		}
		break;
	case USER_TOOLS::ADD_ELEMENT:
		BoardElement* newElement = new BoardElement(idCount++, "Character", xPos, yPos, resources, gui);
		elements.push_back(newElement);
		if (elements.size() == 2) {
			edgeManager.createEdge(elements[0], elements[1]);
		}
		break;
	}

}
void Board::onLeftMouseReleased() {
	std::cout << "Left Released on Board" << std::endl;
	switch (activeTool) {
	case USER_TOOLS::MOVE:
		if (selectedElement != nullptr) {
			selectedElement->release();
			selectedElement = nullptr;
		}
		break;
	}
}

void Board::onRightMousePressed() {
	std::cout << "Right Pressed on Board" << std::endl;
	activeTool = activeTool == USER_TOOLS::MOVE ? USER_TOOLS::ADD_ELEMENT : USER_TOOLS::MOVE;
}
void Board::onRightMouseReleased() {
	std::cout << "Right Released on Board" << std::endl;
}

void Board::onMouseMove(float xPos, float yPos , CursorManager& cursor) {
	switch (activeTool) {
	case USER_TOOLS::MOVE:
		if (selectedElement != nullptr) {
			selectedElement->drag(xPos, yPos);
			edgeManager.onElementMove(selectedElement);
		}
		else {
			for (BoardElement* el : elements) {
				if (el->isHovering(xPos, yPos)) {
					cursor.onHoveringEnter();
					hoveredElement = el;
					break;
				}
				cursor.onHoveringExit();
				hoveredElement = nullptr;
			}
		}
		break;
	}
}

void Board::drawElements(sf::RenderWindow& window) {
	edgeManager.draw(window);
	for (BoardElement* el : elements) {
		el->draw(window);
	}
}

