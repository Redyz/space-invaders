#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
class Entity;
class Window;
class Logic{
	public:
		Logic(Window *window);
		~Logic();

		int getEntityCount();
		void step();
	private:
		std::vector<Entity*> entityVector; 
		int createEntity(Entity *newEntity);
	public:

	private:
		Window *window;
};

#endif
