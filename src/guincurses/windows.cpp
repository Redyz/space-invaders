#include "guincurses/input.h"
#include "guincurses/windows.h"
#include "logic.h"
#include "entity.h"
#include "utility.h"
#include "tr1/memory"
#ifdef IS_NT
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include <vector>
#define SCORE_HEIGHT 2
Window::Window(){
  initscr();
  raw();// -> add quitting functionality first
  noecho(); //disable user getches
  nodelay(stdscr, TRUE); //make getch non-blocking
  keypad(stdscr, TRUE); //enable F1-F12 + arrow keys
  start_color();
  initColors();
	clearok(stdscr, FALSE);
	immedok(stdscr, FALSE);
	idcok(stdscr, FALSE);
	idlok(stdscr, FALSE);
  getmaxyx(stdscr, height, width); //store the screen size
	curs_set(0); //disable cursor
  scoreWindow = newwin(SCORE_HEIGHT, width, 0, 0); //create the score 
  gameWindow = newwin(height-SCORE_HEIGHT, width, SCORE_HEIGHT, 0); //height, width, sy, sx
}

Window::~Window(){
	destroy();
	delete input;
}

void Window::destroy(){
  endwin();
}

void Window::setup(Logic* logic){
  logic->setGameWidth(width-1);
  logic->setGameHeight(height - SCORE_HEIGHT-1);
  this->logic = logic;
  this->input = new Input(logic);
}
void Window::initColors(){
  init_pair(PAIR_ENTITY, COLOR_GREEN, COLOR_BLACK);
  init_pair(PAIR_GHOST, COLOR_YELLOW, COLOR_BLACK);
}
void Window::clearWindow(){
	if(this->logic->getCurrentTick() % 10 == 0)
		werase(scoreWindow);
	werase(gameWindow);
};

void Window::inputStep(){
  input->step();
}
void Window::draw(){
  drawScores();
	drawGame();
  doupdate();
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

void Window::debug(std::string text){
#if IS_DEBUG
  display(text, 25, 0, scoreWindow);
#endif
}

void Window::drawScores(){
  int score = logic->getScore(); 
  std::string stringScore = "Score: " + SSTR(score);
  display(stringScore, 0, 0, scoreWindow);
#if IS_DEBUG
	display(SSTR(" Tick: " << logic->getCurrentTick()), 10, 0, scoreWindow);
#endif
  unsigned int lives = logic->getPlayer()->getLife();
  display(SSTR("Lives: " << lives), width - 9, 0, scoreWindow);
  std::string bottomBorder = "";
  for(int i = 0; i < width; i++){
    bottomBorder += "_";
  }
  display(bottomBorder, 0, 1, scoreWindow);
  wnoutrefresh(scoreWindow);
}

void Window::drawGame(){
  std::vector<Entity*> entityVector = logic->getEntityVector();
  try{
    for(std::vector<Entity*>::iterator it = entityVector.begin(); it != entityVector.end(); it++){
      Entity* currentEntity = *it;
			char displayCar = '!';
      switch(currentEntity->getType()){
        case ENTITY:
        case GHOST:
					displayCar = '@';
          break;
        case BULLET:
					displayCar = '|';
          break;
        case WALL:
					displayCar = 'X';
          break;
        case UFOS:
					displayCar = '#';
          break;
      }
			display(SSTR(displayCar), currentEntity->getX(), currentEntity->getY(), gameWindow);
    }

  }catch(...){
    Logger::log("Exception caught");
  }
  attron(COLOR_PAIR(PAIR_ENTITY));
  display("U", logic->getPlayer()->getX(), logic->getPlayer()->getY(), gameWindow);
  attroff(COLOR_PAIR(PAIR_ENTITY));
  wnoutrefresh(gameWindow);
}
