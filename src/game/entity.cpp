#include "entity.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
Entity::Entity(){
	//std::cout << "Creating a new entity" << std::endl;
}

Entity::~Entity(){
	
}

std::string Entity::toString(){
	std::ostringstream convertingStream;
	convertingStream << "E:" << x << ":" << y;
	return convertingStream.str();
}
