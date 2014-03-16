#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
class Entity;
class Window;
class Message;
enum directions{
  UP,
  DOWN,
  LEFT,
  RIGHT
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
    Entity* getPlayer(){ return this->player; }
    std::vector<Entity*> getEntityVector(){ return entityVector; }
    int getGameHeight(){ return gameHeight;}
    int getGameWidth(){ return gameWidth;}
    void setGameHeight(int height){ gameHeight = height; }
    void setGameWidth(int width){ gameWidth = width; }
    bool isRunning(){ return running; }
    bool setRunning(bool value){ running = value; }
    int createEntity(Entity *newEntity);
  public:
    Window *window;
  private:
    int gameHeight;
    int gameWidth;
    std::vector<Entity*> entityVector; //container for all entities
    std::vector<Entity*> backgroundEntityVector; //such as walls, bullets, etc
    Entity *player;
    int score;
    bool running;

};

#endif
