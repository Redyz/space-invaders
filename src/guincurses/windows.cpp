#include "guincurses/windows.h"
#include "logic.h"
#include "entity.h"
#include "utility.h"
#include <ncurses.h>
#include <vector>
#define SCORE_HEIGHT 2
Window::Window(){
	initscr();
  //raw() -> add quitting functionality first
  noecho(); //disable user getches
  keypad(stdscr, TRUE); //enable F1-F12 + arrow keys
  start_color();
  initColors();
	getmaxyx(stdscr, height, width); //store the screen size
  scoreWindow = newwin(SCORE_HEIGHT, width, 0, 0); //create the score 
  gameWindow = newwin(height-SCORE_HEIGHT, width, SCORE_HEIGHT, 0); //height, width, sy, sx
}

Window::~Window(){
	endwin();
}

void Window::setup(Logic* logic){
  logic->setGameWidth(width);
  logic->setGameHeight(height - SCORE_HEIGHT);
  this->logic = logic;
}
void Window::initColors(){
  init_pair(PAIR_ENTITY, COLOR_GREEN, COLOR_BLACK);
  init_pair(PAIR_GHOST, COLOR_YELLOW, COLOR_BLACK);
}
void Window::clearWindow(){
  wclear(gameWindow);
  wclear(scoreWindow);
};

void Window::draw(){
  drawScores();
  drawGame();
  wmove(gameWindow, logic->getGameWidth(), logic->getGameHeight());
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
  std::vector<Entity*> entityVector = logic->getEntityVector();
  try{
    for(std::vector<Entity*>::iterator it = entityVector.begin(); it != entityVector.end(); it++){
      Entity* currentEntity = *it;
      switch(currentEntity->getType()){
        case ENTITY:
          display("@", currentEntity->getX(), currentEntity->getY(), gameWindow);
          //display(SSTR("X:" << currentEntity->getX()));
          break;
      }

    }

  }catch(...){

  }
  attron(COLOR_PAIR(PAIR_ENTITY));
  display("U", logic->getPlayer()->getX(), logic->getPlayer()->getY(), gameWindow);
  attroff(COLOR_PAIR(PAIR_ENTITY));
  wrefresh(gameWindow);
}
