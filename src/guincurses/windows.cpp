#include "guincurses/windows.h"
#include "logic.h"
#include "entity.h"
#include "utility.h"
#include <ncurses.h>
#include <vector>

Window::Window(){
	initscr();
  //raw() -> add quitting functionality first
  noecho(); //disable user getches
  keypad(stdscr, TRUE); //enable F1-F12 + arrow keys
	getmaxyx(stdscr, height, width); //store the screen size
  scoreWindow = newwin(2, width, 0, 0); //create the score window
  gameWindow = newwin(height-2, width, 2, 0); //height, width, sy, sx
}

Window::~Window(){
	endwin();
}

void Window::clearWindow(){
  wclear(gameWindow);
  wclear(scoreWindow);
};

void Window::draw(Logic* logic){
  this->logic = logic; //this is not efficient, might have to do a setup function instead
  drawScores();
  drawGame();
}

void Window::display(std::string text){
	wprintw(gameWindow, text.c_str());
}

void Window::display(std::string text, int x, int y){
	mvwprintw(gameWindow, y, x, text.c_str());
}

void Window::display(std::string text, int x, int y, WINDOW* window){
  mvwprintw(window, y, x, text.c_str());
}

void Window::drawScores(){
  int score = logic->getScore(); 
  std::string stringScore = SSTR("Score: " << score);
  display(stringScore, 0, 0, scoreWindow);
  int lives = logic->getPlayer()->getLife();
  display(SSTR("Lives: " << lives), width - 9, 0, scoreWindow);
  std::string bottomBorder = "";
  for(int i = 0; i < width; i++){
    bottomBorder += "_";
  }
  display(bottomBorder, 0, 1, scoreWindow);
  wrefresh(scoreWindow);
}

void Window::drawGame(){
  display("Tits", 0, 0, gameWindow);
  std::vector<Entity*> entityVector = logic->getEntityVector();
  try{
    for(std::vector<Entity*>::iterator it = entityVector.begin(); it != entityVector.end(); it++){
      Entity* currentEntity = *it;
      switch(currentEntity->getType()){
        case ENTITY:
          display("@", currentEntity->getX(), currentEntity->getY(), gameWindow);
      }
    }

  }catch(...){

  }
  wrefresh(gameWindow);
}
