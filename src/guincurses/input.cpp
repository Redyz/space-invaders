#include "logic.h"
#include "config.h"
#include "entity.h"
#include "guincurses/input.h"
#ifdef IS_NT
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include <curses.h>
#include <string>
#include "utility.h"
#include "message.h"
#include <sstream>
Input::Input(Logic* logic){
  this->logic = logic;
}

Input::~Input(){

}

void Input::step(){
  int c = getch();
  if(c != ERR){
    switch(c){
      case 27: // Escape key
        logic->setGameState(PAUSED);
        logic->window->menuVisible(true);
        Logger::log("Pressed pause");
        break;
      case 'q':
        logic->notify(new GameOverMessage(QUIT_GAME));
        //logic->setRunning(false);
        break;
      case KEY_UP:
        logic->window->menuUp();
        break;
      case KEY_DOWN:
        logic->window->menuDown();
        break;
      case '\n':
        logic->window->menuSelect();
        break;
      case 'r':
        logic->notify(new ArmageddonMessage());
        Logger::log("ARMAGEDDON!");
        break;
      case 'a':
      case KEY_LEFT:
        if(logic->getGameRunning())
          logic->getPlayer()->move(-1, 0);
        break;
      case 'd':
      case KEY_RIGHT:
        if(logic->getGameRunning())
          logic->getPlayer()->move(1, 0);
        break;
      case ' ':
        if(logic->getGameRunning())
          logic->getPlayer()->fire(UP);
        break;
      default:
#ifdef IS_DEBUG
        Logger::log("Unknown key pressed: " + SSTR(c));
#endif
        break;
    }
  }
}
