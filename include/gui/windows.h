#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include "menu.h"
#include "logic.h"

namespace sf{
  class RenderWindow;;
  class Font;
  class Text;
};

class Input;
class MenuManager;
class VisualMenu;
class WINDOW;
class Window final{
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
    sf::Font* getFont() { return font; }
    void initColors();
    void inputStep();
    void changeMenu(Menu *newMenu);

    //TODO Think this through
    void menuUp() { logic->menu->goUp(); }
    void menuDown() { logic->menu->goDown(); }
    void menuSelect() { logic->menu->getSelected()->do_call(); }
    void menuVisible(bool visible){ logic->menu->setVisible(visible); }
    
    
    MenuManager* menuManager;
  private:
    void drawScores();
    void drawGame();
    void drawMenu();

    VisualMenu *visualMenu;
    sf::RenderWindow *sfWindow;
    sf::Font *font;
    sf::Text *debugText;
    int width;
    int height;
    Logic* logic;
    Input* input;
    
    friend class VisualMenu;
};

#endif
