#include "entity.h"
#include "logic.h"
#include "config.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
Entity::Entity(Logic* logic) : x(0), y(0), type("Entity"), life(3){
  this->logic = logic;
}

Entity::~Entity(){
	
}

std::string Entity::toString(){
	std::ostringstream convertingStream;
	convertingStream << "E:" << x << ":" << y;
	return convertingStream.str();
}

void Entity::move(int modX, int modY){
  x += modX;
  y += modY;
}

void Entity::modLife(int mod){
  logic->window->display("Entity lost life");
  life += mod;
  if(life <= 0){
    life = 0;
    die();
  }
}

void Entity::die(){
  logic->notify(DEATH, this);
}

void Entity::die(Entity* killer){
  logic->notify(DEATH, this);
}
