#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
class Entity;

class Logic{
	public:
		Logic();
		~Logic();

		int getEntityCount();
		void step();
	private:
		std::vector<Entity*> entityVector; 
		int createEntity(Entity *newEntity);
};

#endif
