#include "logic.h"
#include "entity.h"
#include "config.h"
#include "utility.h"
#include "message.h"
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
  int numberOfGhosts = 100;
  Entity *current;
  int currentX = 0, currentY = 0;
  for(int i=0;i<numberOfGhosts;i++){
    current = new Entity(this);
    current->setX(currentX += 2);
    if(currentX >= getGameWidth()-3){
      currentX = 0;
      currentY += 1;
    }
    current->setY(currentY);
    createEntity(current);
  }
  current = new Entity(this);
  player = current; //arbitrary for now
  player->setY(getGameHeight());
  player->setX((int)getGameWidth()/2);
  createEntity(player);
}

int Logic::createEntity(Entity *newEntity){
  entityVector.push_back(newEntity);
  Logger::log("New entity created");
}

void Logic::step(){
  //window->display(SSTR("Width: " << getGameHeight()));
  for(std::vector<Entity*>::iterator it = entityVector.begin(); it != entityVector.end(); it++){
    (*it)->step();
  }
  //if(rand() % 100 > 20){
    //Entity* currentEntity = entityVector.at(static_cast<int>(rand()%entityVector.size()));
    //currentEntity->step();
  //}
}
void Logic::notify(Message *message){
  message->execute(this);
//  delete message;
}

int Logic::deleteEntity(Entity *entity){
  //std::vector<Entity*>::iterator it = std::find(entityVector.begin(), entityVector.end(), entity);
  int before = 0, after = 0;
  before = entityVector.size();
  entityVector.erase(entityVector.begin());
  //entityVector.erase(it);
  after = entityVector.size();
}
