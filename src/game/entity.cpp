#include "../../include/entity.h"
#include "../../include/logic.h"
#include "../../include/config.h"
#include "../../include/message.h"
#include "../../include/utility.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
Entity::Entity(Logic* logic) : x(0), y(0), type(ENTITY), life(1), damage(-1), speed(2){
  this->logic = logic;
  lastAction = 0;
  lastMoved = 0;
  canMove = true;
  canAct = true;
}

Entity::~Entity(){

}

std::string Entity::toString(){
  std::ostringstream convertingStream;
  convertingStream << "E:" << x << ":" << y;
  return convertingStream.str();
}
bool Entity::testMove(int modX, int modY){
  if(x + modX < 0 || x + modX > logic->getGameWidth()){
    return false;
  }
  if(y + modY < 0 || y + modY > logic->getGameHeight()){
    return false;
  }
  return true;
}
bool Entity::move(int modX, int modY){
  if(testMove(modX, modY)){
    int oldX = x, oldY = y;
    x += modX;
    y += modY;
    logic->notifyMove(this, oldX, oldY); //probably best to have a message for this
    lastMoved = logic->getCurrentTick();
    canMove = false;
    return true;
  }else{
    return false;
  }
}

void Entity::modLife(int mod){
  life += mod;
  if(life <= 0){
    life = 0;
    die();
  }
}

void Entity::modLife(int mod, Entity* shooter){
  life += mod;
  Logger::log("Lost life! " + SSTR("Cur: " << life) + ", " + getUniqueId());
  
  if(life <= 0){
    life = 0;
    die(shooter);
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

bool Entity::step(){
  if(logic->getCurrentTick() - lastMoved > speed)
    canMove = true;
  return true;
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
Bullet::Bullet(Logic *logic) : Entity(logic){
  type = BULLET;
  damage = -1; //means you lose 1hp
}
bool Bullet::step(){
  int moveResult;
  
  int modX, modY;
  switch(direction){
    case UP:
      modX = 0, modY = -1;
      //moveResult = testMove(0, -1);
      break;
    case RIGHT:
      modX = -1, modY = 0;
      //moveResult = testMove(-1, 0);
      break;
    case DOWN:
      modX = 0, modY = 1;
      //moveResult = testMove(0, 1);
      break;
    case LEFT:
      modX = -1, modY = 0;
      //moveResult = testMove(-1, 0);
      break;
  }
  //unsuccessful move
  if(!testMove(modX, modY)){
    die();
  }else{
    Entity* collision = logic->testEntityCollision(this, x+modX, y+modY);
    if(collision){
      logic->notify(new HitMessage(this, collision));
      logic->notify(new DeathMessage((this))); //might be bad
    }else{
      move(modX, modY);
    }
  }
}

Ghost::Ghost(Logic* logic) : Entity(logic){
  this->logic = logic;
  travelDirection = RIGHT;
  speed = 10;
}

bool Ghost::step(){
  if(Entity::step() && canMove){
    int modX = 0;
    if(travelDirection == RIGHT){
      modX = 1;
    }else{
      modX = -1;
    }
    if(!move(modX, y)){
      if(move(-modX, y)){ //can go down
        setTravelDirection(travelDirection == RIGHT ? LEFT : RIGHT);
      }else{
        die(); //out of bounds..?
      }
    }
  }
}

void Ghost::setTravelDirection(int direction){
  travelDirection = direction;
}
