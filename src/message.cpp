#include "logic.h"
#include "utility.h"
#include "config.h"
#include "entity.h"
#include "message.h"
#include <vector>
#include <algorithm>

Message::Message(){

}

Message::~Message(){

}

void Message::setId(unsigned int id){
  if(this->messageId == 0)
    this->messageId = id;
  else
    Logger::log("Error: trying to change message id more than once (" + SSTR(this->messageId) + ")");
}

void Message::execute(Logic *logic){

};

bool Message::canExecute(Logic *logic){
  return true;
}

std::string Message::toString(){
  return "Default message";
}
/*
 * DeathMessage class
 */
DeathMessage::DeathMessage(Entity* killed) : Message(){
  this->killed = killed;
}

DeathMessage::DeathMessage(Entity* killed, Entity* killer){
  this->killed = killed;
  this->killer = killer;
  if(killed->getType() == PLAYER)
    Logger::log("Player has been hit");
  if(killed->getType() != BULLET)
    Logger::log("Deleting an entity (" + killed->toString() + "), killed by " + killer->toString());
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

ArmageddonMessage::ArmageddonMessage(){

}

void ArmageddonMessage::execute(Logic* logic){
  auto vect = logic->getEntityVector();
  for(auto entity : vect){
    if(entity->getType() == GHOST)  
      logic->notify(new FireMessage(entity, entity->getX(), entity->getY(), DOWN));
  }
}

/*
 * HitMessage class
 */
HitMessage::HitMessage(Entity* firer, Entity* fired){
  this->firer = firer;
  this->fired = fired;
}

void HitMessage::execute(Logic *logic){
#if IS_DEBUG
  if(firer == NULL)
    Logger::log("Firer is null");
  else if(fired == NULL)
    Logger::log("Fired is null");
  else
    Logger::log(firer->getUniqueId() + " just hit " + fired->getUniqueId());
#endif
  fired->modLife(firer->getDamage(), firer);
}

/*
 * InvertDirectionMessage class
 */
InvertDirectionMessage::InvertDirectionMessage() {

}

void InvertDirectionMessage::execute(Logic* logic){
  std::vector<Entity*> entityVector = logic->getEntityVector();
  for(unsigned int i = 0; i < entityVector.size(); i++){
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
  if(logic->getGameState() != QUITTING){
    std::string gameOverString = "Game is over - ";
    switch(reason){
      case LOST_ALL_LIVES: gameOverString += "you lost all your lives!"; break;
      case REACHED_BOTTOM: gameOverString += "enemies touched the bottom!"; break;
      case NO_MORE_ENEMIES: gameOverString += "You won; You repelled the alien invasion!"; break;
      case QUIT_GAME: gameOverString += "You quit the game!"; break;
    }
    gameOverString += " - Final score: " + SSTR(logic->getScore());
    Logger::log(gameOverString);
    logic->notify(new ConsoleMessage(gameOverString));
    logic->setGameState(QUITTING);
  }
}

/*
 * KillAllEnemiesMessage Class
 */
KillAllEnemiesMessage::KillAllEnemiesMessage() {
  
}

void KillAllEnemiesMessage::execute(Logic* logic){
  for(auto enemy : logic->getEnemyVector()){
    logic->deleteEntity(enemy);
  }
}

ConsoleMessage::ConsoleMessage(std::string message){
  this->message = message;
}

std::string ConsoleMessage::toString(){
  return message;
}

void ConsoleMessage::execute(Logic *logic){
  Logger::log("Processed message " + SSTR(message));
  logic->window->console(message);
}

bool ConsoleMessage::canExecute(Logic *logic){
  return logic->getGameState() != QUITTING;
}
