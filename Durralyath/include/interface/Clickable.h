#pragma once
#include <SFML/Graphics.hpp>
class Clickable
{
protected:
	float xPos, yPos;
	float width, height;
	float hovered;
protected:
	virtual void onHoverEnter();
	virtual void onHoverExit();
public:
	Clickable(float xPos, float yPos, float width, float height);
	bool isHovering(float xCursorPos, float yCursorPos);
	virtual void onMousePressed();
	virtual void onMouseRelease();
	virtual void setPosition(float xPos, float yPos);
	virtual void setDimensions(float width, float height);
	virtual void draw(sf::RenderWindow& window);

};

