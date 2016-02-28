#include "config.h"
#include "utility.h"
#include "logic.h"
#include "entity.h"
#include "SFML/Window/Keyboard.hpp"

Input::Input(Logic *logic){
	this->logic = logic;
}

Input::~Input(){
}

void Input::step(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		logic->setRunning(false);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		logic->getPlayer()->move(-1, 0);
		logic->window->debug("Left");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		logic->getPlayer()->move(1, 0);
		logic->window->debug("Right");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		logic->getPlayer()->fire(UP);
	}
}
