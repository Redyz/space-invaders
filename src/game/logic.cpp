#include "logic.h"
#include "entity.h"
#include "config.h"
#include "utility.h"
#include "message.h"
#include "menu.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <cstdlib>
#include <math.h>
#include <stdexcept>

Logic::Logic(Window *window) : running(true), score(0), currentEntityIndex(0), currentMessageId(0), currentTick(0){
  this->window = window;
  Logger::log("BEGAN NEW SESSION");
}


Logic::~Logic(){
	delete menu;

	// Free all entities
	for(auto current : entityVector)
		delete current;

  entityVector.clear();
  enemyVector.clear();
  gameZones.clear();

	// Seemingly some of this isn't called when the destructor is
	Logger::log("Bye!");
}
void Logic::init(){
	this->menu = new Menu(this);
  currentTick = 0;
  int numberOfGhosts = 500;
  int sideConstant = 5;

  //currently, for curses mode the game zone height is equivalent to the gameHeight
	// bad alloc here with gameheight in SFML mode
#if !IS_SFML
  gameZones.resize(gameHeight+1); //+1? TODO: find out why this is here
  for(unsigned int y = 0; y < gameHeight+1; y++){
    gameZones[y].resize(gameWidth);
    for(unsigned int x = 0; x < gameWidth; x++){
      gameZones[y].push_back(NULL); //instantiate null pointers
    }
  }

  Logger::log("Initializing game session with: " + SSTR("Height: " << gameZones.size()) + SSTR(" Width: " << gameZones[0].size()));
  Entity* current;
  int currentX = sideConstant, currentY = 0;
  for(int i=0;i<numberOfGhosts;i++){
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
  current = new Player(this);
  player = current; //arbitrary for now
  player->setY(getGameHeight());
  player->setX((int)getGameWidth()/2);
  gameZones[current->getY()][current->getX()] = current;
  int totalSpread = getGameWidth() - 4;
  int spacing = totalSpread / (3*5);
  for(int i = 0; i < 5; i++){
    createWall(5+(i*spacing), 5);
  }
  createEntity(player);
#endif
}

int Logic::createEntity(Entity* newEntity){
  newEntity->setUniqueId(SSTR(""<<newEntity->getType()) + SSTR("-" << currentEntityIndex++));
  entityVector.push_back(newEntity);
  //Logger::log("Current entity: "  + SSTR(newEntity->getType()) + " and enemy: " + SSTR("" << ENEMY));
  if(newEntity->getType() & ENEMY){
    //Logger::log("Created an enemy, the type: " + SSTR(newEntity->getType()));
    enemyVector.push_back(newEntity);
  }
  //Logger::log("New entity created: " + newEntity->getUniqueId());
	return 0;
}

bool Logic::createWall(int x, int y){
  try{
    Entity *wall;
    int currentX = 0, currentY = 0;
    for(int row = 0; row < 2; row++){
      for(int i = 0; i < 3; i++){
        if(row != 1){
          wall = new Wall(this);
          currentX = x + i;
          currentY = y + row;
          wall->setX(currentX);
          wall->setY(currentY);
          gameZones[wall->getY()][wall->getX()] = wall;
          createEntity(wall);
        }
      }
    }
  }catch(...){
    Logger::log("Failed to create a wall");
  }
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

void Logic::step(){
	processMessages();
  Entity* current;
  for(unsigned int i = 0; i < entityVector.size(); i++){
    current = entityVector[i];
    current->step(); //the entity may die after .step, don't do anything after it
  }

#if !IS_SFML
	if(enemyVector.size() == 0)
		notify(new GameOverMessage(NO_MORE_ENEMIES));
#endif
  //Logger::log("Current number of enemies: " + SSTR(""<<enemyVector.size()));
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
  std::vector<EntV*> lists;
  if(lists.size() == 0){
    lists.push_back(&entityVector);
    lists.push_back(&enemyVector);
  }
  EntV::iterator current;
  for(unsigned int i = 0; i < lists.size(); i++){
    current = std::find(lists[i]->begin(), lists[i]->end(), entity);
    if(current != lists[i]->end() && *current != 0){
			gameZones[(*current)->getY()][(*current)->getX()] = NULL; //set the pointer to null
			lists[i]->erase(current);
			delete entity;
			return 0;
		}
  }
	return 1;
}
