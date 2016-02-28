#include "gui/windows.h"
#include "logic.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>


static sf::Sprite sprite;
static sf::Texture texture;
Window::Window(){
	sfWindow = new sf::RenderWindow();
	font = new sf::Font();
	debugText = new sf::Text("Hello", *font);
	debugText->setCharacterSize(30);
	debugText->setStyle(sf::Text::Bold);
	debugText->setColor(sf::Color::White);
	//TODO: Portable paths
	font->loadFromFile("fonts/Comprehension-Dark.ttf");
	texture.loadFromFile("assets/img/Spaceship.png");
	sprite.setTexture(texture);
}

Window::~Window(){
	delete sfWindow;
	delete font;
	delete debugText;
}

void Window::setup(Logic *logic){
	sfWindow->create(sf::VideoMode(800, 600), "Window");
	sfWindow->setFramerateLimit(SFML_FRAME_LIMIT);
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
	sfWindow->clear(sf::Color::Blue);
	sfWindow->draw(*debugText);
	sfWindow->draw(sprite);
	sfWindow->display();
}

void Window::debug(std::string text){
	debugText->setString(text);
}

void Window::display(std::string text){
	debug(text);
}

void Window::console(std::string text){
	std::cout << text << std::endl;
}

void Window::destroy(){

}


