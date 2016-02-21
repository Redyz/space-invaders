#ifndef CURSES_MENU_H
#define CURSES_MENU_H

class Logic;

class VisualMenu{
	public:
		VisualMenu(Logic *logic);
		~VisualMenu();

	private:
		Logic *logic;
};
#endif
