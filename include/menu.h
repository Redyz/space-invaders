#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <functional>

class Logic;

class MenuComponent{
  public:
    MenuComponent(Logic *logic, std::string text, std::function<void()> callback); 
    ~MenuComponent();
    bool activate();
    MenuComponent *left, *right, *up, *down;
    std::string text;
    std::function<void()> callback;

  private:
    Logic* logic;
};

class Menu{

  public:
    Menu(Logic *logic);
    ~Menu();

    void goDown();
    void goUp();
    void addMenuComponent(MenuComponent* component);

    MenuComponent* getTop(){ return top; }
    MenuComponent* getSelected(){ return selected; }

    bool isVisible() { return visible; }
    void setVisible(bool visible) { this->visible = visible; }

  private:
    MenuComponent *top;
    MenuComponent *selected;

    bool visible;
};
#endif
