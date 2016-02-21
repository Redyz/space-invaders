#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <cstdlib>
typedef enum entityType{
  ENTITY = 0b1,
  WALL = 0b10,
  BULLET = 0b100,
  TANK = 0b1000,
  GHOST = 0b10000,
  PLAYER = 0b100000
}entityTypes;
typedef enum entityGroup{
    ENEMY = GHOST | BULLET,
    FRIENDLY = PLAYER | WALL
}entityGroups;
class Logic;
class Entity{
  public:
    Entity(Logic* logic);
    virtual ~Entity();

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
    bool isOutsideMap();
    virtual bool step() = 0;
		

    /**
    * Action methods
    * TODO: Implement those instead
    */
protected:
    virtual void doHit(Entity *hitter){}
    virtual void doMove(){}
    virtual void doIncreaseLife(int lifeAmount){}
    virtual void doDecreaseLife(int lifeAmount){}
    virtual void doDie(){}
    virtual void doTickUpdate(){}
    virtual void doFire(){}

  public:

  protected:
    int x;
    int y;
    int life;
    int type;
    int lastMoved;
    int lastAction; //ticks
    int speed;
    int firingSpeed;
    int damage;
    std::string uniqueId;
    Logic* logic;
    bool canMove;
    bool canAct;
};


class Bullet : public Entity{
  public:
    Bullet(Logic *logic, Entity *firer);
    virtual bool step();
    void setDirection(int direction){ this->direction = direction; }
		void die();
  private:
    int direction;
    Entity *firer;
};

class Ghost : public Entity{
public:
  Ghost(Logic *logic);
  virtual bool step();
  void setTravelDirection(int direction);
  void invertTravelDirection();
  bool move(int modX, int modY);
protected:
    virtual void doHit(Entity* hitter);
    int travelDirection;
};

class Player : public Entity{
public:
    Player(Logic *logic);
    virtual bool step();

protected:
    void doDie();
};

class Prop : public Entity{
public:
    Prop(Logic *logic);
    virtual bool step();
    bool move(int modX, int modY);
    
protected:
    int facingDirection;
};

class Wall : public Prop{
public:
    Wall(Logic *logic);
    virtual bool step();
};
#endif
