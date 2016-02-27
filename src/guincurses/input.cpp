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
    //const char *name = keyname( c );
    switch(c){
      case 'q':
			case 27: // Escape key
				logic->notify(new GameOverMessage(QUIT_GAME));
        //logic->setRunning(false);
        break;
      //case KEY_UP:
        //logic->getPlayer()->move(0, -1);
        //break;
      //case KEY_DOWN:
        //logic->getPlayer()->move(0, 1);
        //break;
			case 'w':
				logic->notify(new ArmageddonMessage());
				Logger::log("ARMAGEDDON!");
				break;
      case KEY_LEFT:
        logic->getPlayer()->move(-1, 0);
        break;
      case KEY_RIGHT:
        logic->getPlayer()->move(1, 0);
        break;
      case ' ':
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
