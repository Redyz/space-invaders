#include "logic.h"
#include "entity.h"
#include "config.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
Logic::Logic(Window *window) : score(0){
	this->window = window;
	//std::cout << "Creating the logic" << std::endl;
	for(int i=0;i<10;i++){
		entityVector.push_back(new Entity(this));
	}
  player = entityVector.at(0); //arbitrary for now
	for(int i=0;i<entityVector.size();i++){
		entityVector.at(i)->setX(floor(std::rand() % window->getWidth()));
		entityVector.at(i)->setY(floor(std::rand() % window->getHeight()));
		//window->display(entityVector.at(i)->toString(), 0, 0);
	}
}

Logic::~Logic(){
	//std::cout << "Destructing the logic" << std::endl;
	//todo: cleanup
}

void Logic::step(){
  if(rand() % 100 > 99){
    entityVector.at(0)->modLife(-1);
  }
  if(rand() % 100 > 20){
    entityVector.at(static_cast<int>(rand()%entityVector.size()))->move(
      static_cast<int>(-1 + rand() % 2),
      static_cast<int>(-1 + rand() % 2)
    );
  }
}
void Logic::notify(int messageType, Entity* concernedEntity){
  switch(messageType){
    case PLAYER_KILL:
      score += 2;
    case DEATH:
      window->display("Some entity just died");
      std::vector<Entity*>::iterator it = std::find(entityVector.begin(), entityVector.end(), concernedEntity);
      entityVector.erase(it);
      break;
  }
}
