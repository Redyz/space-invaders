#include "../../include/entity.h"
#include "../../include/logic.h"
#include "../../include/config.h"
#include "../../include/message.h"
#include "../../include/utility.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
Entity::Entity(Logic* logic){
  this->logic = logic;
  x = y = lastAction = lastMoved = 0;
  life = 1;
  damage = -1;
  speed = 2;
  firingSpeed = 10;
  canMove = true;   
  canAct = true;
  type = ENTITY;
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
    doDecreaseLife(-mod);
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
  doDie();
  logic->notify(new DeathMessage(this));
}

void Entity::die(Entity* killer){
  doDie();
  logic->notify(new DeathMessage(this, killer));
}

void Entity::fire(int direction){
  if(canAct){
    lastAction = logic->getCurrentTick();
    canAct = false;
    logic->notify(new FireMessage(this, x, y, direction));
    doFire();
  }
}

bool Entity::step(){
  int currentTick = logic->getCurrentTick();
  if(currentTick - lastMoved > speed){
    canMove = true;
  }
  if(currentTick - lastAction > firingSpeed){
    canAct = true;
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

  // Unsuccessful move
  if(!testMove(modX, modY)){
    die();
    return false;
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

  return true;
}

void Bullet::die(){
  logic->notify(new DeathMessage(this));
}

Ghost::Ghost(Logic* logic) : Entity(logic){
  type = GHOST;
  travelDirection = RIGHT;
  speed = GHOST_SPEED;
  firingSpeed = 15;
  life = 1;
  damage = -1;
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
      logic->notify(new InvertDirectionMessage());
      return false;
      /*}else{
        die(); //out of bounds..?
      }*/
    }
  }
  
  if(canAct){
    int randomInt = rand() % 100;
    if(randomInt > (100-GHOST_FIRE_CHANCE)){
      fire(DOWN);
    }
    canAct = false;
    lastAction = logic->getCurrentTick();
  }
  
  return true;
}

bool Ghost::move(int modX, int modY){
  bool result = Entity::move(modX, modY);
  if(y == logic->getGameHeight())
    logic->notify(new GameOverMessage(REACHED_BOTTOM));
  if(modY > 0){
    unsigned int screenDelta = logic->getGameHeight() - y; 
  }
  return result;
}

void Ghost::doHit(Entity* hitter){
  //logic->notify(new InverDirectionMessage());
  logic->modScore(10);
}

void Ghost::setTravelDirection(int direction){
  travelDirection = direction;
}

void Ghost::invertTravelDirection(){
  travelDirection = (travelDirection == LEFT ? RIGHT : LEFT);
}

UFO::UFO(Logic *logic) : Ghost(logic){
  speed = 3;
  life = 1;
  type = UFOS;
  setX(0);
  setY(0);
  setTravelDirection(RIGHT);
}

void UFO::doHit(Entity *hitter){
  Logger::log("Killed a UFO");
  logic->modScore(500);
}

bool UFO::step(){
  bool moved = Ghost::step();
  if(!moved)
    logic->notify(new DeathMessage(this));
  return moved;
}

Player::Player(Logic* logic) : Entity(logic){
  damage = -2;
  speed = 0;
  firingSpeed = 5;
  life = 3;
  type = PLAYER;
}

bool Player::move(int modX, int modY){
  modY = 0; // prevent all Y moves from player
  return Entity::move(modX, modY);
}

void Player::doHit(Entity* hitter){
  setX(logic->getGameWidth()/2);
  logic->modScore(-500);
}

bool Player::step(){
  return Entity::step();
}

void Player::doDie(){
  logic->notify(new GameOverMessage(LOST_ALL_LIVES));
}

Prop::Prop(Logic* logic) : Entity(logic){
  damage = 0;
  speed = 0;
  firingSpeed = 0;
  life = 3;
}

bool Prop::step(){
  return true;  
}

bool Prop::move(int modX, int modY){
  return true;
}

Wall::Wall(Logic* logic) : Prop(logic){
  type = WALL;
  facingDirection = UP;
  life = 1;
}

bool Wall::step(){
 return true; 
}
