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

}

/*
 * DeathMessage class
 */
DeathMessage::DeathMessage(Entity *killed){
  Message();
  this->killed = killed;
  init();
}

DeathMessage::DeathMessage(Entity *killed, Entity *killer){
  Message();
  this->killed = killed;
  this->killer = killer;
  init();
}

void DeathMessage::execute(Logic *logic){
  logic->window->display("Some entity just died");
  std::vector<Entity*> entityVector = logic->getEntityVector();
  std::vector<Entity*>::iterator it = std::find(entityVector.begin(), entityVector.end(), killed);
  entityVector.erase(it);
}
