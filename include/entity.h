#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity{
	public:
		Entity();
		~Entity();
		
		int getX(){ return x; }
		int getY(){ return y; }
		void setX(int x) { this->x = x; } 
		void setY(int y) { this->y = y; }
		std::string toString();
	private:


	public:
		
	private:
		int x;
		int y;
		std::string type;
};
#endif
