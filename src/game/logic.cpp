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
#include <stdexcept>

Logic::Logic(Window *window) : running(true), score(0), currentEntityIndex(0){
  this->window = window;
  Logger::log("BEGAN NEW SESSION");
}

Logic::~Logic(){
  //std::cout << "Destructing the logic" << std::endl;
  entityVector.clear();
  gameZones.clear();
}
void Logic::init(){
  currentTick = 0;
  int numberOfGhosts = 100;
  int sideConstant = 5;
  //currently, for curses mode the game zone height is equivalent to the gameHeight
  gameZones.resize(gameHeight+1); //+1? TODO: find out why this is here
  for(unsigned int y = 0; y < gameHeight+1; y++){
    gameZones[y].resize(gameWidth);
    for(unsigned int x = 0; x < gameWidth; x++){
      gameZones[y].push_back(NULL); //instantiate null pointers
    }
  }
  Logger::log("Initializing game session with: " + SSTR("Height: " << gameZones.size()) + SSTR(" Width: " << gameZones[0].size()));
  Entity* current;
  int currentX = sideConstant, currentY = 0;
  for(int i=0;i<numberOfGhosts;i++){
    current = new Ghost(this);
    if(currentX >= getGameWidth()-sideConstant){
      currentX = sideConstant;
      currentY += 1;
    }
    current->setX(currentX);
    current->setY(currentY);
    gameZones[current->getY()][current->getX()] = current; //register the entity
    createEntity(current);
    currentX+=2;
  }
  current = new Player(this);
  player = current; //arbitrary for now
  player->setY(getGameHeight());
  player->setX((int)getGameWidth()/2);
  gameZones[current->getY()][current->getX()] = current;
  //gameZones[current->getY()][current->getX()].reset(current.get());
  createEntity(player);
}

int Logic::createEntity(Entity* newEntity){
  newEntity->setUniqueId(SSTR(""<<newEntity->getType()) + SSTR("-" << currentEntityIndex++));
  entityVector.push_back(newEntity);
  //Logger::log("New entity created: " + newEntity->getUniqueId());
}

void Logic::notifyMove(Entity *mover, int oldX, int oldY){
  //std::vector<shared_ptr<Entity> >::iterator current = std::find(entityVector.begin(), entityVector.end(), mover);
  //Logger::log(mover->toString());
  
  gameZones[mover->getY()][mover->getX()] = mover;
  gameZones[oldY][oldX] = NULL; //previous x gets cleared
}

Entity* Logic::testEntityCollision(Entity* tester, int x, int y){
  try{
    Entity* current = gameZones[y][x];
    if(current != tester)
      return current;
    else
      return 0;
  }catch(const std::out_of_range& oor){
    return 0; //out of range exception means you tried getting an invalid pos. in the vector
  }
}

void Logic::step(){
  Entity* current;
  for(unsigned int i = 0; i < entityVector.size(); i++){
    current = entityVector[i];
    entityVector[i]->step(); //the entity may die after .step, don't do anything after it
  }
}
void Logic::notify(Message *message){
  message->init();
  message->execute(this);
  delete message;
}

int Logic::deleteEntity(Entity *entity){
  std::vector<Entity*>::iterator current = std::find(entityVector.begin(), entityVector.end(), entity);
  gameZones[(*current)->getY()][(*current)->getX()] = NULL; //set the pointer to null
  if(current != entityVector.end() && *current != 0){
    //Logger::log((*current)->toString());
    //Logger::log("Deleting an entitysss");
    entityVector.erase(current);
  }
}
