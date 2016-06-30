#include "menumanager.h"


MenuManager::MenuManager(Logic* logic)
{
  this->logic = logic;
  
  setupMainMenu();
  setupAbout();
}

void MenuManager::setupMainMenu()
{
  MAINMENU = new Menu(logic);
  
  MAINMENU->addTopMenuComponent(new MenuComponent(logic, "Start game", 
      [=]{
        MAINMENU->setVisible(false);
        logic->setGameState(UNPAUSED);
      })
  
  );
  
  auto settings = MAINMENU->addMenuComponent(new MenuComponent(logic, "Settings", nullptr));
  auto about = MAINMENU->addMenuComponent(new MenuComponent(logic, "About", [=]{logic->setGameState(QUITTING);}));
  about->setVisible(false);
  settings->setCallback([=]{
    about->setVisible(!about->isVisible());
  });
  settings->setVisible(false);
  MAINMENU->addBottomMenuComponent(new MenuComponent(logic, "Quit game", [=]{logic->setGameState(QUITTING);}));
}

void MenuManager::setupAbout()
{

}


MenuManager::~MenuManager()
{
  delete MAINMENU;
  //delete ABOUTMENU;
}