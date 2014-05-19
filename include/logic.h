#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
class Entity;
class Window;
class Message;

typedef std::vector<Entity*> EntV;
enum directions{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  DUPLEFT,
  DUPRIGHT,
  DDOWNLEFT,
  DDOWNRIGHT
};

class Logic{
  public:
    Logic(Window *window);
    ~Logic();

    int getEntityCount();
    void step();
    void init();
    void notify(Message *message);
    int getScore(){ return score; }
    int getCurrentTick(){ return currentTick; }
    Entity* getPlayer(){ return this->player; }
    //std::shared_ptr<typename Entity> test;
    EntV& getEntityVector(){ return entityVector; }
    int getGameHeight(){ return gameHeight;}
    int getGameWidth(){ return gameWidth;}
    void setGameHeight(int height){ gameHeight = height; }
    void setGameWidth(int width){ gameWidth = width; }
    void incrementTick(){ currentTick++; }
    void notifyMove(Entity *mover, int newX, int newY);
    bool isRunning(){ return running; }
    bool setRunning(bool value){ running = value; }
    int createEntity(Entity* newEntity);
    int deleteEntity(Entity* entity);
    Entity* testEntityCollision(Entity* tester, int x, int y);
  public:
    Window *window;
  private:
    int gameHeight;
    int gameWidth;
    EntV entityVector; //container for all entities
    EntV enemyVector;
    EntV backgroundEntityVector; //such as walls, bullets, etc
    std::vector<EntV> gameZones; //container for the game matrix, indicating presence using coordinates
    Entity* player;
    int score;
    int currentEntityIndex;
    int currentTick;
    bool running;
};

#endif
