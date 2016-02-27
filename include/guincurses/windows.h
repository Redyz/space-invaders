#ifndef WINDOW_H
#define WINDOW_H
#include "config.h"
#include <string>
#ifdef IS_NT
#include <curses.h>
#else
#include <ncurses.h>
#endif
enum colorPairs{
  PAIR_ENTITY = 1,
  PAIR_WALL,
  PAIR_BULLET,
  PAIR_TANK,
  PAIR_GHOST
};

static std::string WALL_IMG[] = { 
"  XX  ", 
" XXXX ", 
"XX  XX"  
};

class Logic;
class Input;
class Window{
  public:
    Window();
    ~Window();
    void draw();
    void debug(std::string text);
    void display(std::string text);
    void display(std::string text, int x, int y);
    void display(std::string text, int x, int y, WINDOW* window);
    void setup(Logic *logic);
    void clearWindow();
		void destroy();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void initColors();
    void inputStep();
  private:
    void drawScores();
    void drawGame();
  private:
    WINDOW* gameWindow;
    WINDOW* scoreWindow;
    int width;
    int height;
    Logic* logic;
    Input* input;
};

#endif
