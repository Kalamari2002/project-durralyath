#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <filesystem>

/**
* BoardElement represents a token in the board. It can dragged around.
*/
class BoardElement
{
private:
	const sf::Font defaultFont{ std::filesystem::path("assets/fonts/Quicksand-VariableFont_wght.ttf") };
	const float BASE_DIMENSION = 200.0f;
	float xPos, yPos;						// element's current position
	float xOrigin, yOrigin;					// element's origin coords (centralizes element for more convenient transforms)
	float cursor_xOffset, cursor_yOffset;	// used to prevent element from snapping to mouse's pos while being dragged
	float labelYOffset;						// used to position label below the portrait
	float height, width;					// height and width of element. basically its bounds/rect
	bool hovered;							// determines if cursor is currently hovering over this element or not
	sf::CircleShape *portrait;				// portrait of the entity/character
	sf::Text label;							// name label displayed below the portrait
	std::string name;						// name of the entity/character
private:
	/**
	* Sets all relevant positions (self, portrait and label) associated with BoardElement to
	* the passed coords. Applies any relevant offsets to positions.
	* @param xPos: the X coord within window where the element will be moved to
	* @param yPos: the Y coord within window where the element will be moved to.
	*/
	void move(float xPos, float yPos);
public:
	bool held;
public:
	BoardElement(float xPos, float yPos);
	BoardElement(std::string name, float xPos, float yPos);

	/**
	* Called wheneve the mouse moves in the window. Checks if the cursor is within the
	* element's bounds, sets hovered to true/false accordingly and recolors portrait 
	* to signalize rather the cursor is hovering over this element or not.
	* @param cursor_xPos: cursor's x position
	* @param cursor_yPos: cursor's y position
	* @return true if cursor is within element bounds
	* @return false if cursor is not within element bounds
	*/
	bool isHovering(float cursor_xPos, float cursor_yPos);
	
	void draw(sf::RenderWindow *window);

	/**
	* Called when mouse moves while element is being held. Sets the position where element
	* is being dragged to by adding the cursor offset to the cursor's current position, then
	* calls move() with the adjusted position.
	*/
	void drag(float cursor_xPos, float cursor_yPos);

	/**
	* Called when user presses left mouse button while hovering over this element.
	* If element isn't being held yet, sets element held to true and computes offset from
	* cursor position during click to element's position (this prevents token from snapping
	* to cursor's position before being dragged).
	* @param cursor_xPos: cursor's x position at time of click
	* @param cursor_yPos: cursor's y position at time of click
	*/
	void hold(float cursor_xPos, float cursor_yPos);

	/**
	* Called when user releasees left mouse button while holding this element. Sets held to false.
	*/
	void release();
};

