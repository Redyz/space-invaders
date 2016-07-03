#include "utility.h"
#include "logic.h"
#include "menu.h"

Menu::Menu() : visible(true){

}

Menu::~Menu() {
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
    if(selected->isVisible() && selected->isSelectable())
      found = true;
  }
}

//TODO: Infinite loop warning
void Menu::goDown(){
  bool found = false;
  while(selected->down != NULL && !found){
    selected = selected->down;
    if(selected->isVisible() && selected->isSelectable())
      found = true;
  }
}

MenuComponent::MenuComponent(Logic *logic, std::string text, std::function<void()> callback) : left(NULL), right(NULL), up(NULL), down(NULL), visible(true), selectable(true) {
  this->logic = logic;
  this->text = text;
  this->originalText = text;
  this->callback = callback;
  this->drawCallback = nullptr;
}

MenuComponent::MenuComponent(Logic *logic, std::string text, std::function<void()> callback, std::function<void()> drawCallback) : MenuComponent(logic, text, callback) {
  this->drawCallback = drawCallback;
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

void MenuComponent::setDrawCallback(std::function<void()> callback)
{
  this->drawCallback = callback;
}

bool MenuComponent::do_call(){
  if(callback != NULL)
    callback();
  return true;
}

bool MenuComponent::do_draw(){
  if(drawCallback!= NULL)
    drawCallback();
  return true;
}

