#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <ncurses.h>
enum colorPairs{
  PAIR_ENTITY,
  PAIR_WALL,
  PAIR_BULLET,
  PAIR_TANK,
  PAIR_GHOST
};
class Logic;
class Window{
	public:
		Window();
		~Window();
		void draw();
		void display(std::string text);
		void display(std::string text, int x, int y);
    void display(std::string text, int x, int y, WINDOW* window);
    void setup(Logic *logic);
		void clearWindow();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void initColors();
  private:
    void drawScores();
    void drawGame();
	private:
    WINDOW* gameWindow;
    WINDOW* scoreWindow;
		int width;
		int height;
    Logic* logic;

};

#endif
