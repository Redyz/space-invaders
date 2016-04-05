#include "utility.h"
#include "include/logic.h"
#include "include/menu.h"

Menu::Menu(Logic *logic) : itemCount(0){
  top = new MenuComponent(logic, "Top", NULL);
  selected = top;

  addMenuComponent(new MenuComponent(logic, "Test1", [=]{Logger::log("Activated!");}));
  addMenuComponent(new MenuComponent(logic, "Test1", [=]{Logger::log("Activated!");}));
  addMenuComponent(new MenuComponent(logic, "Test1", [=]{Logger::log("Activated!");}));
  addMenuComponent(new MenuComponent(logic, "Test1", [=]{Logger::log("Activated!");}));
  addMenuComponent(new MenuComponent(logic, "Test1", [=]{Logger::log("Activated!");}));
  addMenuComponent(new MenuComponent(logic, "Test1", [=]{Logger::log("Activated!");}));
  addMenuComponent(new MenuComponent(logic, "Test3", NULL));
  addMenuComponent(new MenuComponent(logic, "Test2", NULL));
  addMenuComponent(new MenuComponent(logic, "Test2", NULL));
  addMenuComponent(new MenuComponent(logic, "Test2", NULL));
  addMenuComponent(new MenuComponent(logic, "Test2", NULL));
  addMenuComponent(new MenuComponent(logic, "Quit", [=]{logic->setRunning(false);}));

  // Link top to bottom and vice versa
  selected->down = top;
  top->up = selected;

  // Put back selection on top
  selected = top;
}

Menu::~Menu(){
  unsigned int deletedItemCount = 0;
  MenuComponent *current, *old;
  current = top;
  do{
    old = current;
    current = current->down;
    deletedItemCount++;
    delete old;
  }while(deletedItemCount != itemCount);

  delete current;
}

void Menu::addMenuComponent(MenuComponent* component){
  itemCount++;
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
