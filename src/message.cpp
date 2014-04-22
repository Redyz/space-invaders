#include "logic.h"
#include "utility.h"
#include "config.h"
#include "entity.h"
#include "message.h"
#include <vector>
#include <algorithm>

Message::Message(){

}

void Message::init(){

}

Message::~Message(){

}

void Message::execute(Logic *logic){

};
/*
 * DeathMessage class
 */
DeathMessage::DeathMessage(Entity* killed) : Message(){
  this->killed = killed;
  init();
}

DeathMessage::DeathMessage(Entity* killed, Entity* killer){
  this->killed = killed;
  this->killer = killer;
  init();
}

void DeathMessage::execute(Logic *logic){
  logic->deleteEntity(killed);
}

/*
 * FireMessage class
 */
FireMessage::FireMessage(Entity* firer, int startX, int startY, int direction){
  this->startX = startX;
  this->startY = startY;
  this->direction = direction;
  this->firer = firer;
}

void FireMessage::execute(Logic *logic){
  Bullet *bulletEntity = new Bullet(logic);
  bulletEntity->setX(startX);
  bulletEntity->setY(startY);
  bulletEntity->setDirection(direction);
  logic->window->debug("Created a new bullet");
  logic->createEntity(bulletEntity);
}

/*
 * HitMessage class
 */
HitMessage::HitMessage(Entity* firer, Entity* fired){
  this->firer = firer;
  this->fired = fired;
}

void HitMessage::execute(Logic *logic){
  Logger::log(firer->getUniqueId() + " just hit " + fired->getUniqueId());
  fired->modLife(fired->getDamage(), firer);
}