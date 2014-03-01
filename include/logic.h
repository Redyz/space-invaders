#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
class Entity;
class Window;


enum messageType{
  DEATH
};

class Logic{
	public:
		Logic(Window *window);
		~Logic();

		int getEntityCount();
		void step();
    void notify(int messageType, Entity* concernedEntity);
	private:
		int createEntity(Entity *newEntity);
	public:
		Window *window;
	private:
		std::vector<Entity*> entityVector; //container for all entities
    std::vector<Entity*> backgroundEntityVector; //such as walls, bullets, etc
    Entity *player;
};

#endif
