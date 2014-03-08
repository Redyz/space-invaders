#include "entity.h"
#include "logic.h"
#include "config.h"
#include "message.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
Entity::Entity(Logic* logic) : x(0), y(0), type(ENTITY), life(3){
  this->logic = logic;
}

Entity::~Entity(){

}

std::string Entity::toString(){
  std::ostringstream convertingStream;
  convertingStream << "E:" << x << ":" << y;
  return convertingStream.str();
}

int Entity::move(int modX, int modY){
  if(x + modX < 0 || x + modX > logic->getGameWidth()){
    return 1;
  }
  if(y + modY < 0 || y + modY > logic->getGameHeight()){
    return 1;
  }
  x += modX;
  y += modY;
  return 0;
}

void Entity::modLife(int mod){
  logic->window->display("Entity lost life");
  life += mod;
  if(life <= 0){
    life = 0;
    die(0);
  }
}

int Entity::getLife(){
  return life;
}
void Entity::die(){
  logic->notify(new DeathMessage(this));
}

void Entity::die(Entity* killer){
  logic->notify(new DeathMessage(this, killer));
}

void Entity::fire(int direction){
  logic->notify(new FireMessage(this, x, y, direction));
}

void Entity::step(){

}

bool Entity::outsideMap(){
  int gameHeight = logic->getGameHeight();
  int gameWidth = logic->getGameWidth();
  if(x < 0 || x > gameWidth)
    return true;
  if(y < 0 || y > gameHeight)
    return true;
  return false;
}
/**
 * Bullet entity class
 */
void Bullet::step(){
  int moveResult;
  switch(direction){
    case UP:
      moveResult = move(0, -1);
      break;
    case RIGHT:
      moveResult = move(-1, 0);
      break;
    case DOWN:
      moveResult = move(0, 1);
      break;
    case LEFT:
      moveResult = move(-1, 0);
      break;
  }
  //unsuccessful move
  if(moveResult != 0){
    logic->notify(new DeathMessage(this));
  }
}
