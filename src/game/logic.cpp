#include "logic.h"
#include "entity.h"
#include "config.h"
#include "utility.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
Logic::Logic(Window *window) : running(true), score(0){
  this->window = window;
}

Logic::~Logic(){
  //std::cout << "Destructing the logic" << std::endl;
  entityVector.clear();
}
void Logic::init(){
  for(int i=0;i<10;i++){
    entityVector.push_back(new Entity(this));
  }
  player = entityVector.at(0); //arbitrary for now
  for(int i=0;i<entityVector.size();i++){
    entityVector.at(i)->setX(floor(std::rand() % getGameWidth()));
    entityVector.at(i)->setY(floor(std::rand() % getGameHeight()));
  }
}

void Logic::step(){
  //window->display(SSTR("Width: " << getGameHeight()));
  if(rand() % 100 > 20){
    Entity* currentEntity = entityVector.at(static_cast<int>(rand()%entityVector.size()));
    if(currentEntity != player)
      currentEntity->move(
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
