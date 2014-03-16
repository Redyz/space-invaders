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
    int move(int modX, int modY);
    void modLife(int mod);
    int getLife();
    int getType(){ return type; }
    void die();
    void die(Entity* killer);
    void fire(int direction);
    std::string toString();
    void step();
  private:
    bool outsideMap();

  public:

  protected:
    int x;
    int y;
    int life;
    int type;
    int lastMoved;
    int lastAction; //ticks
    int speed;
    Logic* logic;
};


class Bullet : public Entity{
  public:
    Bullet(Logic *logic);
    void step();
    void setDirection(int direction){ this->direction = direction; }
  private:
    int direction;
};
#endif
