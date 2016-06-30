#include "utility.h"
#include "logic.h"
#include "menu.h"

Menu::Menu(Logic *logic) : visible(true){
  
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

MenuComponent* Menu::addMenuComponent(MenuComponent* component){
  selected->down = component;
  component->up = selected;
  selected = component;
  
  return component;
}

MenuComponent* Menu::addBottomMenuComponent(MenuComponent* component)
{
  addMenuComponent(component);
  this->selected->down = this->top;
  this->top->up = this->selected;
  this->selected = this->top;
  return component;
}

MenuComponent* Menu::addTopMenuComponent(MenuComponent* component)
{
  this->top = component;
  this->selected = this->top;
  return component;
}


void Menu::goUp(){
bool found = false;
  while(selected->up != NULL && !found){
    selected = selected->up;
    if(selected->isVisible())
      found = true;
  }
}

//TODO: Infinite loop warning
void Menu::goDown(){
  bool found = false;
  while(selected->down != NULL && !found){
    selected = selected->down;
    if(selected->isVisible())
      found = true;
  }
}

MenuComponent::MenuComponent(Logic *logic, std::string text, std::function<void()> callback) : left(NULL), right(NULL), up(NULL), down(NULL), visible(true) {
  this->logic = logic;
  this->text = text;
  this->originalText = text;
  this->callback = callback;
}

MenuComponent::~MenuComponent(){

}

void MenuComponent::revertText()
{
  text = originalText;
}

void MenuComponent::setText(std::string newText)
{
  text = newText;
}

void MenuComponent::setCallback(std::function<void()> callback)
{
  this->callback = callback;
}

bool MenuComponent::activate(){
  if(callback != NULL)
    callback();
  return true;
}
