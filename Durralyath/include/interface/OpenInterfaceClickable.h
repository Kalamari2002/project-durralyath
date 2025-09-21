#pragma once
#include "interface/Clickable.h"
#include "interface/UInterface.h"
class OpenInterfaceClickable : public Clickable
{
private:
	UInterface& uInterface;
public:
	OpenInterfaceClickable(float xPos, float yPos, float width, float height, UInterface& uInterface) :
		Clickable(xPos, yPos, width, height), uInterface(uInterface) {}
	void onMousePressed() override {
		uInterface.activate();
	}
};

