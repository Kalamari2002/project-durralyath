#include "app/App.h"
App::App() : 
	window(sf::VideoMode(sf::Vector2u(c_WINDOW_WIDTH, c_WINDOW_HEIGHT)), "Durralyath"),
	gui(window),
	cursorManager(window)
{
	board = new Board("Board", resources, interfaceManager,gui);
}

App::~App() {
	delete board;
}

void App::pollEvents() {
	while (const std::optional event = window.pollEvent()) {

		gui.handleEvent(*event);

		if (event->is<sf::Event::Closed>()) window.close();
		float xPos = sf::Mouse::getPosition(window).x;
		float yPos = sf::Mouse::getPosition(window).y;
		if (event->is<sf::Event::MouseMoved>()) {
			board->onMouseMove(xPos, yPos, cursorManager);
		}
		if (event->is<sf::Event::MouseButtonPressed>()) {
			if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
				board->onLeftMousePressed(xPos, yPos);
			}
			if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right) {
				board->onRightMousePressed();
			}
		}
		if (event->is<sf::Event::MouseButtonReleased>()) {
			if (event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left) {
				board->onLeftMouseReleased();
			}

		}
	}
}

void App::run() {
	while (window.isOpen()) {
		pollEvents();
		window.clear(c_DEFAULT_BACKGROUND_COLOR);
		board->drawElements(window);
		gui.draw();
		window.display();
	}
}