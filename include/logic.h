#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <deque>

class Entity;
class Window;
class Message;
class Menu;

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

#define GHOST_FIRE_CHANCE 95
#define UFO_SPAWN_TIMER  60 // in seconds
#define SFML_FRAME_LIMIT 60 // in FPS

class Logic{
  public:
    Logic(Window *window);
    ~Logic();

    int getEntityCount();
    void step();
    void init();
    void notify(Message *message);
		void processMessages();
    int getScore(){ return score; }
		void modScore(int mod){ score += mod; }
    int getCurrentTick(){ return currentTick; }
    Entity* getPlayer(){ return this->player; }
    EntV& getEntityVector(){ return entityVector; }
    int getGameHeight(){ return gameHeight;}
    int getGameWidth(){ return gameWidth;}
    void setGameHeight(int height){ gameHeight = height; }
    void setGameWidth(int width){ gameWidth = width; }
    void incrementTick(){ currentTick++; }
    void notifyMove(Entity *mover, int newX, int newY);
    bool isRunning(){ return running; }
    void setRunning(bool value){ running = value; }
    bool createWall(int x, int y);
    int createEntity(Entity* newEntity);
    int deleteEntity(Entity* entity);
    Entity* testEntityCollision(Entity* tester, int x, int y);
  public:
    Window *window;
  private:
    unsigned int gameHeight;
    unsigned int gameWidth;
		Menu *menu;
    EntV entityVector; //container for all entities
    EntV enemyVector;
    //EntV backgroundEntityVector; //such as walls, bullets, etc
    std::vector<EntV> gameZones; //container for the game matrix, indicating presence using coordinates
    Entity* player;
    bool running;
    int score;
    int currentEntityIndex;
		int currentMessageId;
    int currentTick;

		std::deque<Message*> messageDeque;
};

#endif
