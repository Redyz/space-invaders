#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include "menu.h"

namespace sf{
  class RenderWindow;;
  class Font;
  class Text;
};

class Logic;
class Input;
class MenuManager;
class WINDOW;
class Window{
  public:
    Window();
    ~Window();
    void draw();
    void console(std::string text);
    void debug(std::string text);
    void display(std::string text);
    void display(std::string text, int x, int y);
    void display(std::string text, int x, int y, WINDOW* window);
    void display_center(std::string text);
    void setup(Logic *logic);
    void configText(sf::Text &text);
    void clearWindow();
    void destroy();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void initColors();
    void inputStep();
    void changeMenu(Menu *newMenu);

    //TODO Think this through
    void menuUp() { menu->goUp(); }
    void menuDown() { menu->goDown(); }
    void menuSelect() { menu->getSelected()->do_call(); }
    void menuVisible(bool visible){ this->menu->setVisible(visible); }
    
    
    MenuManager* menuManager;
  private:
    void drawScores();
    void drawGame();
    void drawMenu();

    Menu* menu;
    sf::RenderWindow *sfWindow;
    sf::Font *font;
    sf::Text *debugText;
    int width;
    int height;
    Logic* logic;
    Input* input;
};

#endif
