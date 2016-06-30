#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "menu.h"
#include "logic.h"

class Logic;

class MenuManager{
public:
  MenuManager(Logic *logic);
  ~MenuManager();
  
  Menu *MAINMENU;
  Menu *ABOUTMENU;
  
private:
  void setupMainMenu();
  void setupAbout();
  
  Logic *logic;
};


#endif