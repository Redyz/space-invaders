#include "guincurses/windows.h"
#include <ncurses.h>

Window::Window(){
	initscr();
	printw("Howdy ncurses");
	refresh();
}

Window::~Window(){
	endwin();
}

void Window::draw(){
	printw("More curses");
	refresh();
	getch();
}
