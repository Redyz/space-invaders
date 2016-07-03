#pragma once

#include <iostream>
#include <functional>

class Logic;
class MenuManager;

class MenuComponent final {
  public:
    MenuComponent(Logic *logic, std::string text, std::function<void()> callback);
    MenuComponent(Logic *logic, std::string text, std::function<void()> callback, std::function<void()> drawCallback);
    ~MenuComponent();
    void setText(std::string newText);
    void revertText();
    void setCallback(std::function<void()> callback);
    void setDrawCallback(std::function<void()> callback);
    MenuComponent *left, *right, *up, *down;
    std::string text;
    std::string originalText;

    bool isVisible() { return visible; }
    void setVisible(bool visible) { this->visible = visible; }

    bool isSelectable() { return selectable; }
    void setSelectable(bool selectable) { this->selectable = selectable; }

    bool do_call();
    bool do_draw();
  private:
    Logic* logic;
    bool visible;
    bool selectable;
    std::function<void()> callback;
    std::function<void()> drawCallback;

};

class Menu final {

  public:
    Menu();
    ~Menu();

    void goDown();
    void goUp();
    MenuComponent* addMenuComponent(MenuComponent* component);
    MenuComponent* addTopMenuComponent(MenuComponent* component);
    MenuComponent* addBottomMenuComponent(MenuComponent* component);

    MenuComponent* getTop(){ return top; }
    MenuComponent* getBottom(){ return bottom; }
    MenuComponent* getSelected(){ return selected; }

    bool isVisible() { return visible; }
    void setVisible(bool visible) { this->visible = visible; }

  private:
    MenuComponent *top;
    MenuComponent *bottom;
    MenuComponent *selected;

    bool visible;

    friend class Window;
    friend class MenuManager;
};
