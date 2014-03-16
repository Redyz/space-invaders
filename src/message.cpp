#include "logic.h"
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
DeathMessage::DeathMessage(Entity *killed) : Message(){
  this->killed = killed;
  init();
}

DeathMessage::DeathMessage(Entity *killed, Entity *killer){
  this->killed = killed;
  this->killer = killer;
  init();
}

void DeathMessage::execute(Logic *logic){
  std::vector<Entity*> entityVector = logic->getEntityVector();
  std::vector<Entity*>::iterator it = std::find(entityVector.begin(), entityVector.end(), killed);
  entityVector.erase(it);
}

/*
 * FireMessage class
 */
FireMessage::FireMessage(Entity *firer, int startX, int startY, int direction){
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
