#include "tr1/memory"
#include "guincurses/input.h"
#include "guincurses/windows.h"
#include "logic.h"
#include "entity.h"
#include "utility.h"
#include "menu.h"

#include <stdlib.h>

#ifdef IS_NT
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include <vector>

const std::string WALL_IMG[] = { 
"  XX  ", 
" XXXX ", 
"XX  XX"  
};

#if IS_UTF8
const std::string GHOST_CHAR = "⚫";
const std::string BULLET_CHAR = "⚡";
const std::string WALL_CHAR = "☰";
const std::string UFO_CHAR = "☯";
const std::string PLAYER_CHAR = "☗";
#else
const std::string GHOST_CHAR = "@";
const std::string BULLET_CHAR = "|";
const std::string WALL_CHAR = "X";
const std::string UFO_CHAR = "#";
const std::string PLAYER_CHAR = "U";
#endif

#define SCORE_HEIGHT 2
Window::Window(){
  initscr();
  raw();// -> add quitting functionality first
  noecho(); //disable user getches
  nodelay(stdscr, true); //make getch non-blocking
  keypad(stdscr, true); //enable f1-f12 + arrow keys
  getmaxyx(stdscr, height, width); //store the screen size
  curs_set(0); //disable cursor
  scoreWindow = newwin(SCORE_HEIGHT, width, 0, 0); //create the score 
  gameWindow = newwin(height-SCORE_HEIGHT, width, SCORE_HEIGHT, 0); //height, width, sy, sx
  start_color();
  initColors();
  clearok(stdscr, FALSE);
  immedok(stdscr, FALSE);
  idcok(stdscr, FALSE);
  idlok(stdscr, FALSE);

}

Window::~Window(){
  destroy();
  delete input;
  delete menu;
}

void Window::destroy(){
  endwin();
}

void Window::setup(Logic* logic){
  logic->setGameWidth(width-1);
  logic->setGameHeight(height - SCORE_HEIGHT-1);
  this->logic = logic;
  this->input = new Input(logic);

  this->menu = new Menu(logic);
}
void Window::initColors(){
  init_pair(PAIR_ENTITY, COLOR_GREEN, COLOR_BLACK);
  init_pair(PAIR_GHOST, COLOR_GREEN, COLOR_BLACK);
  init_pair(PAIR_WALL, COLOR_WHITE, COLOR_BLACK);
  init_pair(PAIR_UFO, COLOR_RED, COLOR_WHITE);
  init_pair(PAIR_BULLET, COLOR_YELLOW, COLOR_BLACK);
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
  drawMenu();
  drawGame();
  wnoutrefresh(gameWindow);
  wnoutrefresh(scoreWindow);
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

void Window::console(std::string text){
  std::cout << text << std::endl;
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
  display(SSTR("Level: " << logic->getCurrentLevel()), width - 20, 0, scoreWindow);
  std::string bottomBorder = "";
  for(int i = 0; i < width; i++){
#if IS_UTF8
    bottomBorder += "☷";
#else
    bottomBorder += "_";
#endif
  }
  display(bottomBorder, 0, 1, scoreWindow);
}

void Window::drawGame(){
  std::vector<Entity*> entityVector = logic->getEntityVector();
  try{
    for(std::vector<Entity*>::iterator it = entityVector.begin(); it != entityVector.end(); it++){
      Entity* currentEntity = *it;
      unsigned int colorPair = 0;
      std::string displayCar = "!";
      switch(currentEntity->getType()){
        case ENTITY:
        case GHOST:
          displayCar = GHOST_CHAR;
          colorPair = PAIR_GHOST;
          break;
        case BULLET:
          displayCar = BULLET_CHAR;
          colorPair = PAIR_BULLET;
          break;
        case WALL:
          displayCar = WALL_CHAR;
          colorPair = PAIR_WALL;
          break;
        case UFOS:
          wattron(gameWindow, A_BOLD);
          displayCar = UFO_CHAR;
          colorPair = PAIR_UFO;
          break;
      }
      wattron(gameWindow, COLOR_PAIR(colorPair));
      display(SSTR(displayCar), currentEntity->getX(), currentEntity->getY(), gameWindow);
      wattroff(gameWindow, COLOR_PAIR(colorPair));
      wattroff(gameWindow, A_BOLD);
    }

  }catch(...){
    Logger::log("Exception caught");
  }
  wattron(gameWindow, COLOR_PAIR(PAIR_BULLET));
  display(SSTR(PLAYER_CHAR), logic->getPlayer()->getX(), logic->getPlayer()->getY(), gameWindow);
  wattroff(gameWindow, COLOR_PAIR(PAIR_BULLET));
}

void Window::drawMenu(){
  if(!menu->isVisible())
    return;
  int currentInd = 0;
  int textOffset = 0;
  MenuComponent* current = menu->getTop();

  //TODO: Clean me up
  if(logic->getGameState() == PAUSED)
    current->setText("Unpause game");
  else
    current->setText("Start game");
    
  do{
    textOffset = current->text.size()/2;
    
    //TODO Currently impossible to have something selected and not visible
    if(current == menu->getSelected())
      display(SSTR(">" << current->text << "<"), logic->getGameWidth()/2 + textOffset+1 - (current->text.length()+2) , logic->getGameHeight()/2 + currentInd, gameWindow);
    else{
      if(current->isVisible())
	display(current->text, logic->getGameWidth()/2 + textOffset - current->text.length(), logic->getGameHeight()/2 + currentInd, gameWindow);
      else
	currentInd--; //Not very pretty
    }
    current = current->down;
    currentInd++;
  }while(current != menu->getTop());
}

void Window::menuUp(){
  menu->goUp();
}

void Window::menuDown(){
  menu->goDown();
}

void Window::menuSelect(){
  menu->getSelected()->activate();
}

void Window::menuVisible(bool visible){
  menu->setVisible(visible);
}
