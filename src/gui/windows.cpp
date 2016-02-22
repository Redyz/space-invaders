#include "gui/windows.h"
#include "logic.h"
#include <SFML/Window.hpp>


Window::Window(){
	sfWindow = new sf::Window();
}

Window::~Window(){
	delete sfWindow;
}

void Window::setup(Logic *logic){
	sfWindow->create(sf::VideoMode(800, 600), "Window");
}

void Window::clearWindow(){

}

void Window::inputStep(){
	sf::Event event;
	while (sfWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
					sfWindow->close();
	}

}

void Window::draw(){

}

void Window::debug(std::string text){

}


