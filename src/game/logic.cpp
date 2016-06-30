#include "config.h"
#include "logic.h"
#include "entity.h"
#include "utility.h"
#include "message.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
#include <stdexcept>

//TODO: unify gameState and running
Logic::Logic(Window *window) : state(START), score(0), currentEntityIndex(0), currentMessageId(10), currentTick(0), currentLevel(1){
  Logger::log("BEGAN NEW SESSION");
  this->window = window;
}


Logic::~Logic(){

  // Free all entities
  for(auto current : entityVector)
    delete current;

  entityVector.clear();
  enemyVector.clear();
  gameZones.clear();

  Logger::log("Bye!");
}

void Logic::init(){
  currentTick = 0;
  unsigned int numberOfGhosts = currentLevel * NUMBER_OF_GHOST;
  unsigned int sideConstant = 5;

  // currently, for curses mode the game zone height is equivalent to the gameHeight
  gameZones.resize(gameHeight+1);
  for(unsigned int y = 0; y < gameHeight+1; y++){
    gameZones[y].resize(gameWidth);
    for(unsigned int x = 0; x < gameWidth; x++){
      gameZones[y].push_back(NULL); //instantiate null pointers
    }
  }

  Logger::log("Initializing game session with: " + SSTR("Height: " << gameZones.size()) + SSTR(" Width: " << gameZones[0].size()));
  Entity* current;
  unsigned int currentX = sideConstant, currentY = 0;
  for(unsigned int i=0;i<numberOfGhosts;i++){
    current = new Ghost(this);
    if(currentX >= getGameWidth()-sideConstant){
      currentX = sideConstant;
      if(currentY+1 > gameHeight){
        Logger::log("Too many ghosts for screen size; skipping some");
        break;
      }
      currentY += 1;
    }
    current->setX(currentX);
    current->setY(currentY);
    gameZones[current->getY()][current->getX()] = current; //register the entity
    createEntity(current);
    currentX+=2;
  }
  unsigned int totalSpread = getGameWidth() - 4;
  unsigned int spacing = 11;
  unsigned int yPos = getGameHeight() - 5;
  unsigned int numberOfWalls = (unsigned int)totalSpread/11;
  for(unsigned int i = 0; i < numberOfWalls; i++)
    createWall(5+(i*spacing), yPos);

  current = new Player(this);
  player = current; //arbitrary for now
  player->setY(getGameHeight());
  player->setX((int)getGameWidth()/2);
  gameZones[current->getY()][current->getX()] = current;
  createEntity(player);

  //notify(new DisplayCenterMessage("GOWD", 3));
  
}

int Logic::createEntity(Entity* newEntity){
  newEntity->setUniqueId(SSTR(newEntity->getType()) + SSTR("-" << currentEntityIndex++));
  entityVector.push_back(newEntity);
  if(newEntity->getType() & ENEMY)
    enemyVector.push_back(newEntity);
  return 0;
}

bool Logic::createWall(int x, int y){
#if !IS_SFML
  try{
    Entity *wall;
    int currentX = 0, currentY = 0;
    for(unsigned int curY = 0; curY < 3; curY++){
      for(unsigned int curX = 0; curX < WALL_IMG[curY].length(); curX++){
        char current = WALL_IMG[curY][curX];
        if(current == 'X'){
          wall = new Wall(this);
          currentX = x + curX;
          currentY = y + curY;
          wall->setX(currentX);
          wall->setY(currentY);
          gameZones[wall->getY()][wall->getX()] = wall;
          createEntity(wall);
        }
      }
    }
    return true;
  }catch(...){
    Logger::log("Failed to create a wall");
  }
#endif
  return false;
}

void Logic::notifyMove(Entity *mover, int oldX, int oldY){
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

void Logic::processMessages(){
  std::deque<Message*>::iterator it = messageDeque.begin();
  while(it != messageDeque.end()){
    Message* current = *it;
    Logger::log("Trying to process unprocessed message " + current->toString());
    if(current->canExecute(this)){
      current->execute(this);
      it = messageDeque.erase(it);
      delete current;
    }else
      ++it;
  }
}

void Logic::reset()
{
  for(auto entity : getEntityVector())
    deleteEntity(entity);
  getEntityVector().clear();
  enemyVector.clear();
}

static unsigned int lastSpawnedUfo = 0; 
void Logic::step(){
  processMessages();
  Entity* current;
  if(currentTick - lastSpawnedUfo > 100 && getSecondsSinceStart() % UFO_SPAWN_TIMER == 0){
    createEntity(new UFO(this));
    Logger::log(SSTR(getSecondsSinceStart()) + " seconds elapsed");
    lastSpawnedUfo = currentTick;
  }
  for(unsigned int i = 0; i < entityVector.size(); i++){
    current = entityVector[i];
    current->step(); //the entity may die after .step, don't do anything after it
  }

  //TODO Game levels
  if(enemyVector.size() == 0){
    currentLevel++;
    reset();
    init();
    //notify(new GameOverMessage(NO_MORE_ENEMIES));
  }
    
}

int Logic::getSecondsSinceStart(){
  int seconds;
#if IS_SFML
  seconds = getCurrentTick()*(1000/SFML_FRAME_LIMIT)/1000;
#else
  seconds = getCurrentTick()*TICK_LENGTH/1000;
#endif
  return seconds;
}

void Logic::notify(Message *message){
  message->setId(currentMessageId++);
  if(message->canExecute(this)){
    message->execute(this);
    delete message;
  }else
    messageDeque.push_back(message);
}

int Logic::deleteEntity(Entity *entity){
  auto positionEntity = std::find(entityVector.begin(), entityVector.end(), entity);
  auto positionEnemy = std::find(enemyVector.begin(), enemyVector.end(), entity);
  if(positionEntity != entityVector.end()){
  
    // Remove entity from enemy vector
    if(positionEnemy != enemyVector.end())
      positionEnemy = enemyVector.erase(positionEnemy);  
      
    gameZones[(*positionEntity)->getY()][(*positionEntity)->getX()] = NULL; //set the pointer to null
    delete *positionEntity;
    positionEntity = entityVector.erase(positionEntity);
    return 0;
  }
return 1;
}
