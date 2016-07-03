#pragma once

#include "menu.h"
#include "logic.h"

class Logic;

class MenuManager final {
public:
  MenuManager(Logic *logic);
  ~MenuManager();

  Menu *MAINMENU;
  Menu *ABOUTMENU;
  Menu *LOSTLIFE;

private:
  void setupMainMenu();
  void setupAbout();
  void setupLostLife();

  Logic *logic;
};
