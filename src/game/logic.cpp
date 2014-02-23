#include "logic.h"
#include "entity.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
Logic::Logic(){
	std::cout << "Creating the logic" << std::endl;
	for(int i=0;i<10;i++){
		entityVector.push_back(new Entity());
	}
}

Logic::~Logic(){
	std::cout << "Destructing the logic" << std::endl;
	//todo: cleanup
}

void Logic::step(){
	for(int i=0;i<entityVector.size();i++){
		entityVector.at(i)->setX(floor(std::rand() % 100));
		entityVector.at(i)->setY(floor(std::rand() % 100));
		std:: cout << entityVector.at(i)->toString() << std::endl;
	}
}

