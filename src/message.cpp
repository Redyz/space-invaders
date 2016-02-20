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
}

DeathMessage::DeathMessage(Entity* killed, Entity* killer){
  this->killed = killed;
  this->killer = killer;
  if(killed->getType() != BULLET)
    Logger::log("Deleting an entity, killed by " + killer->toString());
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
  Bullet *bulletEntity = new Bullet(logic, firer);
  bulletEntity->setX(startX);
  bulletEntity->setY(startY);
  bulletEntity->setDirection(direction);
  //logic->window->debug("Created a new bullet");
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
  //Logger::log(firer->getUniqueId() + " just hit " + fired->getUniqueId());
  fired->modLife(firer->getDamage(), firer);
}

/*
 * InvertDirectionMessage class
 */
InvertDirectionMessage::InvertDirectionMessage() {

}

void InvertDirectionMessage::execute(Logic* logic){
  std::vector<Entity*> entityVector = logic->getEntityVector();
  for(int i = 0; i < entityVector.size(); i++){
    Entity *currentEntity = entityVector[i];
    if(currentEntity->getType() == GHOST){
      Ghost *currentGhost = static_cast<Ghost*>(currentEntity);
      currentGhost->invertTravelDirection();
      currentGhost->move(0, 1);
    }
  }
}

/*
 * GameOverMessage Class
 */
GameOverMessage::GameOverMessage(int reason) {
  this->reason = reason;
}

void GameOverMessage::execute(Logic* logic){
  //Since this can happen multiple times, let's mute it
  if(logic->isRunning()){
    std::string gameOverString = "Game is over - ";
    switch(reason){
      case LOST_ALL_LIVES: gameOverString += "you lost all your lives!"; break;
      case REACHED_BOTTOM: gameOverString += "enemies touched the bottom!"; break;
    }
    Logger::log(gameOverString);
    logic->setRunning(false);
  }
}
