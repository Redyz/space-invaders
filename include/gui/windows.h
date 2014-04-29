#ifndef WINDOW_H
#define WINDOW_H
#include <string>

class Logic;
class Input;
class WINDOW;
class Window{
  public:
    Window();
    ~Window();
    void draw();
    void debug(std::string text);
    void display(std::string text);
    void display(std::string text, int x, int y);
    void display(std::string text, int x, int y, WINDOW* window);
    void setup(Logic *logic);
    void clearWindow();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void initColors();
    void inputStep();
  private:
    void drawScores();
    void drawGame();
  private:
    //todo: SFML replace
    //WINDOW* gameWindow;
    //WINDOW* scoreWindow;
    int width;
    int height;
    Logic* logic;
    Input* input;
};

#endif
