#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <cstdlib>
enum entityType{
  ENTITY,
  WALL,
  BULLET,
  TANK,
  GHOST
};
class Logic;
class Entity{
	public:
		Entity(Logic* logic);
		~Entity();
		
		int getX(){ return x; }
		int getY(){ return y; }
		void setX(int x) { this->x = x; } 
		void setY(int y) { this->y = y; }
    void move(int modX, int modY);
    void modLife(int mod);
    int getLife();
    int getType(){ return type; }
    void die();
    void die(Entity* killer);
		std::string toString();
	private:


	public:
		
	private:
		int x;
		int y;
    int life;
		int type;
    Logic* logic;
};
#endif
