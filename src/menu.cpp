#include "include/logic.h"
#include "include/menu.h"

Menu::Menu(Logic *logic){

}


Menu::~Menu(){

}

void Menu::goUp(){
	if(selected->up != NULL)
		selected = selected->up;
}

void Menu::goDown(){
	if(selected->down != NULL)
		selected = selected->down;
}

MenuComponent::MenuComponent(Logic *logic){

}


MenuComponent::~MenuComponent(){

}


bool MenuComponent::activate(){

	return true;
}
