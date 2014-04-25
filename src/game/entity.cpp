#include "../../include/entity.h"
#include "../../include/logic.h"
#include "../../include/config.h"
#include "../../include/message.h"
#include "../../include/utility.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
Entity::Entity(Logic* logic) : x(0), y(0), type(ENTITY), life(1), damage(-1), speed(2), firingSpeed(10){
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
    //Logger::log(SSTR("Game height: " << logic->getGameWidth()) + SSTR(" current: " << x+modX));
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
    this->doMove();
    return true;
  }else{
    return false;
  }
}

void Entity::modLife(int mod){
  life += mod;
  if(mod > 0){
    doIncreaseLife(mod);
  }else{
    doDecreaseLife(-1*mod);
  }
  if(life <= 0){
    life = 0;
    die();
  }
}

void Entity::modLife(int mod, Entity* shooter){
  life += mod;
  if(mod > 0){
    doIncreaseLife(mod);
  }else{
    doDecreaseLife(-1*mod);
    doHit(shooter);
  }
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
  doDie();
}

void Entity::die(Entity* killer){
  logic->notify(new DeathMessage(this, killer));
  doDie();
}

void Entity::fire(int direction){
  logic->notify(new FireMessage(this, x, y, direction));
  doFire();
}

bool Entity::step(){
  int currentTick = logic->getCurrentTick();
  if(currentTick - lastMoved > speed){
    canMove = true;
  }else{
    //Logger::log("Can't move");
  }
  if(currentTick - lastAction > firingSpeed){
    canAct = true;
    /*if(type == GHOST)
      Logger::log("Can act");*/
  }
  doTickUpdate();
  return true;
}

bool Entity::isOutsideMap(){
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
Bullet::Bullet(Logic *logic, Entity *firer) : Entity(logic){
  type = BULLET;
  this->firer = firer;
  damage = -1; //means you lose 1hp
}
bool Bullet::step(){
  int modX, modY;
  switch(direction){
    case UP:
      modX = 0, modY = -1;
      break;
    case RIGHT:
      modX = -1, modY = 0;
      break;
    case DOWN:
      modX = 0, modY = 1;
      break;
    case LEFT:
      modX = -1, modY = 0;
      break;
  }
  //unsuccessful move
  if(!testMove(modX, modY)){
    die();
  }else{
    Entity* collision = logic->testEntityCollision(this, x+modX, y+modY);
    if(collision){ //friendly fire is off!
      if(collision->getType() != firer->getType())
        logic->notify(new HitMessage(this, collision)); //friendly fire is off
      logic->notify(new DeathMessage((this))); //might be bad
    }else{
      move(modX, modY);
    }
  }
}

Ghost::Ghost(Logic* logic) : Entity(logic){
  type = GHOST;
  travelDirection = RIGHT;
  speed = 10;
  firingSpeed = 4;
}

bool Ghost::step(){
  if(Entity::step() && canMove){
    int modX = 0;
    if(travelDirection == RIGHT){
      modX = 1;
    }else{
      modX = -1;
    }
    if(!move(modX, 0)){
      logic->notify(new InverDirectionMessage());
      /*}else{
        die(); //out of bounds..?
      }*/
    }
  }
  
  if(canAct){
    if(rand() % 100 < 1){
      fire(DOWN);
      canAct = false;
      lastAction = logic->getCurrentTick();
    }
  }else{
    //Logger::log("Can't even act");
  }
}

void Ghost::doHit(Entity* hitter){
  //logic->notify(new InverDirectionMessage());
}

void Ghost::setTravelDirection(int direction){
  travelDirection = direction;
}

void Ghost::invertTravelDirection(){
  travelDirection = (travelDirection == LEFT ? RIGHT : LEFT);
}
