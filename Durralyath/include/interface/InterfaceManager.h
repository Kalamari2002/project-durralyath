#pragma once
#include <vector>
#include "interface/UInterface.h"

class InterfaceManager
{
private:
	std::vector<UInterface*> interfaces;
public:
	UInterface* activeInterface;
	UInterface* hoveredInterface;
public:
	InterfaceManager();
	
	void setActiveInterface(UInterface* interface);
	void deactivateInterface();
	void switchInterface(UInterface* interface);
	void subscribe(UInterface* interface);
	void unsubscribe(UInterface* interface){}

	void onKeyPressed(const sf::Keyboard::Scan scancode);
	void onMousePress(float cursor_xPos, float cursor_yPos);
	bool isHovering(float cursor_xPos, float cursor_yPos);
};

