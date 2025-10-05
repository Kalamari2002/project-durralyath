#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <map>

#include "config.h"
#include "board/BoardElement.h"
#include "interface/EditableText.h"
#include "app/Resources.h"

class EdgeManager
{
private:
	class Edge {
	private:
		const float PI = 3.1415926;
		const float LINE_THICKNESS = 10.0f;
		BoardElement* vertices[2];
		std::string labelText;
		EditableText labelTag;
	public:
		sf::RectangleShape line;

		Edge(BoardElement* vertex1, BoardElement* vertex2, std::string text,
			sf::Font& font, tgui::Gui& gui) :
		labelText(text),
		labelTag(labelText, font, gui)
		{
			vertices[0] = vertex1;
			vertices[1] = vertex2;

			line.setFillColor(c_DEFAULT_LINE_COLOR);
			labelTag.centralize(true, false);

			onVertexMoved();
		}

		void onVertexMoved() {
			sf::Vector2f ver1Pos = vertices[0]->getPosition();
			sf::Vector2f ver2Pos = vertices[1]->getPosition();

			float xDiff = ver1Pos.x - ver2Pos.x;
			float yDiff = ver1Pos.y - ver2Pos.y;

			float lineLength = std::sqrt(xDiff * xDiff + yDiff * yDiff);

			line.setSize(sf::Vector2f(lineLength, LINE_THICKNESS));

			sf::Vector2f dimensions = line.getSize();
			line.setOrigin(dimensions / 2.0f);

			float xMid = (ver1Pos.x + ver2Pos.x) / 2.0f;
			float yMid = (ver1Pos.y + ver2Pos.y) / 2.0f;

			line.setPosition(sf::Vector2f(xMid, yMid));
			float rads = std::atan2f(yDiff, xDiff);

			line.setRotation(sf::radians(rads));

			labelTag.setPosition(xMid, yMid);

		}

		void draw(sf::RenderWindow& window) {
			window.draw(line);
			labelTag.draw(window);
		}
	};
	std::vector<Edge*> edges;
	Resources& resources;
	tgui::Gui& gui;
	std::map<unsigned int, std::vector<Edge*>> neighborMap;
public:
	EdgeManager(Resources& resources, tgui::Gui& gui);
	~EdgeManager();

	void onElementMove(BoardElement* element);
	void createEdge(BoardElement* vertex1, BoardElement* vertex2);
	void draw(sf::RenderWindow& window);
};

