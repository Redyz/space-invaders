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
    bool testMove(int modX, int modY);
    bool move(int modX, int modY);
    void modLife(int mod);
    void modLife(int mod, Entity* shooter);
    int getLife();
    int getType(){ return type; }
    int getDamage(){ return damage; }
    void die();
    void die(Entity* killer);
    void fire(int direction);
    std::string toString();
    std::string getUniqueId(){ return uniqueId; }
    void setUniqueId(std::string uniqueId){ this->uniqueId = uniqueId; }
    void setDamage(int damage){ this->damage = damage; }
    virtual bool step();
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
    int damage;
    std::string uniqueId;
    Logic* logic;
    bool canMove;
    bool canAct;
};


class Bullet : public Entity{
  public:
    Bullet(Logic *logic);
    virtual bool step();
    void setDirection(int direction){ this->direction = direction; }
  private:
    int direction;
};

class Ghost : public Entity{
public:
  Ghost(Logic *logic);
  virtual bool step();
  void setTravelDirection(int direction);
protected:
  int travelDirection;
};

#endif
