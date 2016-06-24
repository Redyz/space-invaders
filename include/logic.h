#ifndef LOGIC_H
#define LOGIC_H
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
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
  DUPLEFT, // diagonals
  DUPRIGHT,
  DDOWNLEFT,
  DDOWNRIGHT
};

enum gameState{
  START,
  PAUSED,
  UNPAUSED,
  QUITTING
};

#define GHOST_FIRE_CHANCE 70
#define UFO_SPAWN_TIMER  60 // in seconds
#define SFML_FRAME_LIMIT 60 // in FPS
#define TICK_LENGTH 40
#define NUMBER_OF_GHOST 100

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
    int getSecondsSinceStart();
    Entity* getPlayer(){ return this->player; }
    EntV& getEntityVector(){ return entityVector; }
    int getGameHeight(){ return gameHeight;}
    int getGameWidth(){ return gameWidth;}
    void setGameHeight(int height){ gameHeight = height; }
    void setGameWidth(int width){ gameWidth = width; }
    void incrementTick(){ currentTick++; }
    void notifyMove(Entity *mover, int newX, int newY);
    gameState getGameState(){ return state; }
    bool getGameRunning() { return (state == UNPAUSED); }
    void setGameState(gameState state){ this->state = state; }
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
    std::vector<EntV> gameZones; //container for the game matrix, indicating presence using coordinates
    Entity* player;
    gameState state;
    int score;
    int currentEntityIndex;
    int currentMessageId;
    int currentTick;

    std::deque<Message*> messageDeque;
};

#endif
