#ifndef MENU_H
#define MENU_H


class Logic;

class MenuComponent{
	public:
		MenuComponent(Logic *logic);
		~MenuComponent();
		bool activate();
		MenuComponent *left, *right, *up, *down;
	private:
		std::string text;
};

class Menu{

	public:
		Menu(Logic *logic);
		~Menu();

		void goDown();
		void goUp();

		MenuComponent* getTop(){ return top; }
		MenuComponent* getSelected(){ return selected; }

	private:
		MenuComponent *top;
		MenuComponent *selected;
};
#endif
