#include "interface/InterfaceManager.h"
#include <iostream>

InterfaceManager::InterfaceManager() : activeInterface(nullptr){}

void InterfaceManager::setActiveInterface(UInterface* interface) {
	activeInterface = interface;
}

void InterfaceManager::deactivateInterface() {
	if (activeInterface != nullptr) activeInterface->deactivate();
	activeInterface = nullptr;
}

void InterfaceManager::switchInterface(UInterface* interface) {
	if (interface == activeInterface) return;
	if (activeInterface != nullptr) activeInterface->deactivate();
	activeInterface = interface;
}

void InterfaceManager::subscribe(UInterface* interface) {
	std::cout << "subscribed" << std::endl;
	interfaces.push_back(interface);
}

void InterfaceManager::onKeyPressed(const sf::Keyboard::Scan scancode) {
	if (activeInterface->onKeyPressed(scancode)) {
		activeInterface = nullptr;
	}
}


void InterfaceManager::onMousePress(float cursor_xPos, float cursor_yPos) {
	if (activeInterface != nullptr) {
		if (!activeInterface->isWithinBounds(cursor_xPos, cursor_yPos) && activeInterface->onClickAway()) {
			activeInterface = nullptr;
		};
	}
}