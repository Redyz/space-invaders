#include "menumanager.h"
#include "config.h"
#include "utility.h"

MenuManager::MenuManager(Logic* logic)
{
  this->logic = logic;
  
  setupMainMenu();
  setupAbout();
  setupLostLife();
}

void MenuManager::setupMainMenu()
{
  MAINMENU = new Menu(logic);
  
  MAINMENU->addTopMenuComponent(new MenuComponent(logic, "Start game", 
      [=]{
        MAINMENU->setVisible(false);
        logic->setGameState(UNPAUSED);
      },
      [=]{
	MAINMENU->top->setText(logic->getGameState() == START ? "Start game" : "Unpause game");
      }  
  ));
  
  auto settings = MAINMENU->addMenuComponent(new MenuComponent(logic, "Settings", nullptr));
  auto about = MAINMENU->addMenuComponent(new MenuComponent(logic, "About", 
    [=]{
      logic->window->changeMenu(ABOUTMENU);
    }
  ));
  settings->setCallback([=]{
    
  });
  MAINMENU->addBottomMenuComponent(new MenuComponent(logic, "Quit game", [=]{logic->setGameState(QUITTING);}));
}

void MenuManager::setupAbout()
{
  ABOUTMENU = new Menu(logic);
  ABOUTMENU->addTopMenuComponent(new MenuComponent(logic, "Back", 
    [=]{
      logic->window->changeMenu(MAINMENU);
    }
  ));
  auto line = ABOUTMENU->addMenuComponent(new MenuComponent(logic, "MIT License", nullptr));  line->setSelectable(false);
  line = ABOUTMENU->addMenuComponent(new MenuComponent(logic, std::string("Space-Invaders ") + std::string(VERSION), nullptr));  line->setSelectable(false);
  line = ABOUTMENU->addMenuComponent(new MenuComponent(logic, "Programmed with love and anger by Redyz", nullptr));  line->setSelectable(false);
  auto last = ABOUTMENU->addBottomMenuComponent(new MenuComponent(logic, " ", nullptr));
  last->setSelectable(false);
}

void MenuManager::setupLostLife(){
  LOSTLIFE = new Menu(logic);
  LOSTLIFE->addTopMenuComponent(new MenuComponent(logic, "Go", 
    [=]{
      
      logic->window->changeMenu(MAINMENU);
      logic->setGameState(UNPAUSED);
    }
  ));
  
  auto last = LOSTLIFE->addBottomMenuComponent(new MenuComponent(logic, "You lost a life!", nullptr)); last->setSelectable(false);
}


MenuManager::~MenuManager()
{
  delete MAINMENU;
  delete ABOUTMENU;
  delete LOSTLIFE;
}