#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "window/CursorManager.h"
#include "board/BoardElement.h"
#include "app/Resources.h"

/**
* Main class that's responsible for keeping track of elements, drawing them 
* and providing interaction with them.
*/
class Board
{
private:
	std::vector<BoardElement*> elements;	// Contains all elements in a board
	BoardElement* selectedElement;			// Used to keep track of which element is currently selected for actions
	BoardElement* hoveredElement;			// Used to keep track of which element the cursor is currently hovering over
	Resources& resources;					// Reference for shared resources
	unsigned int id;						// Unique identifier of a board
	enum USER_TOOLS { CURSOR, MOVE, ADD_ELEMENT };	// List of all tools can be used
	USER_TOOLS activeTool;							// Determines the tool that's currently being used
	tgui::Gui& gui;

public:
	std::string name;						// Board name
public:
	Board(std::string name, Resources& resources, tgui::Gui& gui);
	Board(std::string name, unsigned int id, Resources& resources, tgui::Gui& gui);
	~Board();

	/**
	* These functions are all called when their respective event happens. Board does
	* different things in response depending on which tool is currently being used.
	*/
	void onLeftMousePressed(float xPos, float yPos);
	void onLeftMouseReleased();

	void onRightMousePressed();
	void onRightMouseReleased();

	void onMouseMove(float xPos, float yPos, CursorManager& cursor);

	void drawElements(sf::RenderWindow& window);
};

