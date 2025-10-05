#include "board/EdgeManager.h"

EdgeManager::EdgeManager(Resources& resources, tgui::Gui& gui):
resources(resources),
gui(gui)
{}

EdgeManager::~EdgeManager() {
	neighborMap.clear();
	for (Edge* edge : edges) {
		delete edge;
	}
}

void EdgeManager::createEdge(BoardElement* vertex1, BoardElement* vertex2) {
	Edge* newEdge = new Edge(vertex1, vertex2, "Friends", resources.regularTextFont, gui);
	edges.push_back(newEdge);
	neighborMap[vertex1->getId()].push_back(newEdge);
	neighborMap[vertex2->getId()].push_back(newEdge);
}

void EdgeManager::draw(sf::RenderWindow& window) {
	if (edges.size() == 0) return;
	for (Edge* edge : edges) {
		window.draw(edge->line);
	}
}

void EdgeManager::onElementMove(BoardElement* element) {
	if (auto search = neighborMap.find(element->getId()); search == neighborMap.end()) return;
	for (Edge* edge : neighborMap[element->getId()]) {
		edge->onVertexMoved();
	}
}