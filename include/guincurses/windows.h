#ifndef WINDOW_H
#define WINDOW_H
#include "config.h"
#include <string>
#ifdef IS_NT
#include <curses.h>
#else
#include <ncurses.h>
#endif

class Menu;

enum colorPairs{
  PAIR_ENTITY = 1,
  PAIR_WALL,
  PAIR_BULLET,
  PAIR_TANK,
  PAIR_GHOST,
  PAIR_UFO
};

extern const std::string WALL_IMG[];

//'chars' are strings because of utf8, sue me
extern const std::string GHOST_CHAR;
extern const std::string BULLET_CHAR;
extern const std::string WALL_CHAR;
extern const std::string UFO_CHAR;
extern const std::string PLAYER_CHAR;

class Logic;
class Input;
class MenuManager;
class Window final{
  public:
    Window();
    ~Window();
    void draw();
    void debug(std::string text);
    void console(std::string text);
    void display(std::string text);
    void display(std::string text, int x, int y);
    void display(std::string text, int x, int y, WINDOW* window);
    void display_center(std::string text);
    void setup(Logic *logic);
    void clearWindow();
    void destroy();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void initColors();
    void inputStep();
    void changeMenu(Menu *newMenu);
    
    //TODO Think this through
    void menuUp();
    void menuDown();
    void menuSelect();
    void menuVisible(bool visible);
    
    MenuManager* menuManager;
  private:
    void drawScores();
    void drawGame();
    void drawMenu();
  private:
    WINDOW* gameWindow;
    WINDOW* scoreWindow;
    int width;
    int height;
    Logic* logic;
    Input* input;
};

#endif
