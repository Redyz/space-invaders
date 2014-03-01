#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
class Entity;
class Window;

enum messageType{
  DEATH,
  PLAYER_KILL
};

class Logic{
	public:
		Logic(Window *window);
		~Logic();

		int getEntityCount();
		void step();
    void notify(int messageType, Entity* concernedEntity);
    int getScore(){ return score; }
    Entity* getPlayer(){ return this->player; }
    std::vector<Entity*> getEntityVector(){ return entityVector; }
	private:
		int createEntity(Entity *newEntity);
	public:
		Window *window;
	private:
		std::vector<Entity*> entityVector; //container for all entities
    std::vector<Entity*> backgroundEntityVector; //such as walls, bullets, etc
    Entity *player;
    int score;

};

#endif
