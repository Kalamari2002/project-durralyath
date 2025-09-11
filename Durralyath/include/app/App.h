#pragma once
#include <SFML/Graphics.hpp>
#include "app/Resources.h"
#include "board/Board.h"
#include "window/CursorManager.h"
#include "config.h"
/**
* Runs the application. Instantiates the window, resources and objects needed
* to run the application.
*/
class App
{
/**
* An important reminder of raw objects vs pointers:
* Notice how resources is created as a raw object and not a pointer, because its lifetime is the same as app's.
* There really isn't a reason to allocate dynamic memory to this member variable, cause its lifetime is predictable
* and limited.
* However, if we are storing things that might be created, deleted and rearranged in runtime (like a vector of Board objects),
* it makes more sense to store pointers to Board objects instead of raw objects. Suppose you store boards as a vector of raw
* objects. User creates board 1, board 2, board3... If the user decides to delete board 2, your code would have to get rid of it
* with erase. Since raw objects are stored on the stack, you'd have a chunk of empty data between board 1 and board 3, and
* you'd need time to move/copy Board objects to fill that gap. On the other hand, if you have a pointer to a chunk of allocated
* memory in the heap, you can just deallocate it and not have to move other board objects around.
*/
private:
	Resources resources;			// Holds shared resources like textures, fonts, etc.
	sf::RenderWindow window;		// Main window
	CursorManager cursorManager;	// In charge of changing cursor
	Board* board;					// Board where elements are created, drawn, interacted with
private:
	/**
	* Uses window to check for events happening on screen. Calls specific object functions when
	* certain events happen. (I wonder if a mediator pattern would work well here? Maybe objects could
	* just subscribe to mouse clicks for eg. this way app doesn't have to call every single object)
	*/
	void pollEvents();
public:
	App();
	~App();

	/**
	* App loop:
	* 1. Poll events
	* 2. Clear previous frame
	* 3. Draw new frame
	* 4. Display new frame
	*/
	void run();
};

