#include "utility.h"
#include "include/logic.h"
#include "include/menu.h"

Menu::Menu(Logic *logic) : visible(true){
  top = new MenuComponent(logic, "Start game", 
      [=]{
        Logger::log("Activated!");
        setVisible(false);
        logic->setGameState(UNPAUSED);
      });
  selected = top;

  addMenuComponent(top);
  addMenuComponent(new MenuComponent(logic, "Quit", [=]{logic->setGameState(QUITTING);}));

  // Link top to bottom and vice versa
  selected->down = top;
  top->up = selected;

  // Put back selection on top
  selected = top;
}

Menu::~Menu(){
  MenuComponent *current, *old;
  current = top;
  current->up->down = NULL; // destroy link between last and first
  do{
    old = current;
    current = current->down;
    delete old;
    old = NULL;
  }while(current != NULL);
}

void Menu::addMenuComponent(MenuComponent* component){
  selected->down = component;
  component->up = selected;
  selected = component;
}

void Menu::goUp(){
	if(selected->up != NULL)
		selected = selected->up;
}

void Menu::goDown(){
	if(selected->down != NULL)
		selected = selected->down;
}

MenuComponent::MenuComponent(Logic *logic, std::string text, std::function<void()> callback) : left(NULL), right(NULL), up(NULL), down(NULL) {
  this->logic = logic;
  this->text = text;
  this->callback = callback;
}

MenuComponent::~MenuComponent(){

}

bool MenuComponent::activate(){
  if(callback != NULL)
    callback();
	return true;
}
