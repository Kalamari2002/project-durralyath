#pragma once
#include <string>
class TextBox
{
private:
	float xPos, yPos;
public:
	bool isOpen;
	std::string value;
public:
	
	TextBox();

	void open();
	void close();
};

