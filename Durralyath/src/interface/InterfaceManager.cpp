#include "interface/InterfaceManager.h"
#include <iostream>

InterfaceManager::InterfaceManager() : activeInterface(nullptr), hoveredInterface(nullptr){}

void InterfaceManager::setActiveInterface(UInterface* interface) {
	activeInterface = interface;
	activeInterface->activate();
}

void InterfaceManager::deactivateInterface() {
	if (activeInterface != nullptr) activeInterface->deactivate();
	activeInterface = nullptr;
}

void InterfaceManager::switchInterface(UInterface* interface) {
	if (interface == activeInterface) return;
	if (activeInterface != nullptr) activeInterface->deactivate();
	activeInterface = interface;
	activeInterface->activate();
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
	if (hoveredInterface == nullptr) { // Click on nothing
		if (activeInterface != nullptr && activeInterface->onClickAway()) { // if active interface closes on click away
			deactivateInterface();
		}
	}
	else { // Click on something
		if (activeInterface == nullptr) {
			setActiveInterface(hoveredInterface);
		}
		else {
			switchInterface(hoveredInterface);
		}
	}

}

bool InterfaceManager::isHovering(float cursor_xPos, float cursor_yPos) {
	for (UInterface* interface : interfaces) {
		if (interface->isWithinBounds(cursor_xPos, cursor_yPos)) {
			hoveredInterface = interface;
			return true;
		}
	}
	hoveredInterface = nullptr;
	return false;
}