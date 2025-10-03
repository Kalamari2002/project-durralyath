#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"

class UInterface
{
private:
	bool isActive, isVisible;
	sf::RectangleShape frame;
protected:
	float xPos, yPos;
	float xOrigin, yOrigin;
	float width, height;
public:
	
	UInterface(float xPos, float yPos, bool isVisible = true);
	UInterface(float xPos, float yPos, float width, float height, bool isVisible = true);
	
	virtual void activate();
	virtual void deactivate();
	virtual void centralize(bool centralizeX=true, bool centralizeY=true);
	virtual void setPosition(float xPos, float yPos);
	virtual void setDimensions(float width, float height);
	virtual void setOrigin(float xOrigin, float yOrigin);
	virtual void draw(sf::RenderWindow& window);
	
	virtual bool onKeyPressed(sf::Keyboard::Scan scancode);
	virtual bool onClickAway();
	
	void setIsVisible(bool isVisible);
	bool getIsActive();
	bool isWithinBounds(float cursor_xPos, float cursor_yPos);

};

