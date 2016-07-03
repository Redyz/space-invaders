#ifndef VISUAL_MENU_H
#define VISUAL_MENU_H

#include <SFML/Graphics/Text.hpp>

class Logic;
class Window;
class Menu;
class MenuElement;
class MenuComponent;

class VisualMenu{
    
  public: 
    VisualMenu(Logic* logic, Menu* menu);
    ~VisualMenu();
      
    void changeMenu(Menu *menu);
    void draw();
    void reset();
    void deleteElements();
  private:
    std::vector<MenuElement*> menuElements;
    Logic *logic;
    Menu* menu;
};

class VisualElement : public sf::Drawable, public sf::Transformable{
  public:
    VisualElement();
    ~VisualElement();
};

class MenuElement : VisualElement{
  public:
    MenuElement();
    
  private:
    MenuComponent *linkedComponent;
    
    friend class VisualMenu;
    
};
#endif