#include "config.h"
#include "menu.h"
#include "utility.h"
#include <logic.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>

VisualMenu::VisualMenu(Logic* logic, Menu *menu)
{
  this->logic = logic;
  this->menu = menu;
  
  reset();
}

VisualMenu::~VisualMenu()
{
  deleteElements();
}


void VisualMenu::changeMenu(Menu* menu)
{
  this->menu = menu;
  this->reset();
}

void VisualMenu::deleteElements()
{
  for(auto current : menuElements)
    delete current;
  menuElements.clear();
}

void VisualMenu::reset()
{
  deleteElements();
  unsigned int currentX, currentY;
  currentY = logic->window->getHeight()/2;
  currentX = logic->window->getWidth()/2;
  MenuComponent* current = menu->getTop();
  MenuElement *menuElement = nullptr;
  while(current != nullptr && current != menu->getBottom()){
    //TODO: oh god this is sickening
    sf::Text *textElement = new sf::Text(current->text, *logic->window->getFont());
    int middleX = currentX - textElement->getLocalBounds().width/2;
    int elementHeight = textElement->getLocalBounds().height;
    std::cout << currentX << " " << middleX << std::endl;
    
    menuElement = (MenuElement*) (sf::Drawable*) textElement;
    menuElement->linkedComponent = current;
    //currentVisual = (VisuatextElement;
    menuElement->setPosition(middleX, currentY);
    
    currentY += elementHeight + 5;
    menuElements.push_back(menuElement);
    current = current->down;
  }
}

void VisualMenu::draw()
{
  for(MenuElement* current : menuElements){
    Logger::log("Drawing another");
    if(current->linkedComponent == menu->getSelected()){
      std::string baseString = current->linkedComponent->text;
      //dynamic_cast<sf::Text*>(current)->setString("AYYY");
      //((sf::Text*)current)->setString(">" + baseString + "<");
    }
    //this is probably not the way to go
    //logic->window->sfWindow->draw(*(sf::Drawable*)(current));
  }
}

VisualElement::VisualElement()
{
}

VisualElement::~VisualElement()
{

}

MenuElement::MenuElement()
{
}


