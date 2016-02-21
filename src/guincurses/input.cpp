#include "logic.h"
#include "entity.h"
#include "guincurses/input.h"
#include <ncurses.h>
#include <curses.h>
#include <string>
#include "config.h"
#include <sstream>
Input::Input(Logic* logic){
  this->logic = logic;
}

Input::~Input(){

}

void Input::step(){
  int c = getch();
  if(c != ERR){
    const char *name = keyname( c );
    std::string fullText = "You wanted: " + c;
    std::stringstream ss;
    ss << *name;
    ss >> fullText;
    //char secondCharacter;
    switch(c){
      case 'q':
        logic->setRunning(false);
        break;
      case KEY_UP:
        logic->getPlayer()->move(0, -1);
        break;
      case KEY_DOWN:
        logic->getPlayer()->move(0, 1);
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
    }
  }
}
