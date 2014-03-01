#include "guincurses/windows.h"
#include <ncurses.h>

Window::Window(){
	initscr();
	printw("Howdy ncurses");
	getmaxyx(stdscr, width, height); //store the screen size
	refresh();
}

Window::~Window(){
	endwin();
}

void Window::clearWindow(){
  clear();
};

void Window::draw(){
	refresh();
}

void Window::display(std::string text){
	printw(text.c_str());
}

void Window::display(std::string text, int x, int y){
	mvprintw(x, y, text.c_str());
}

