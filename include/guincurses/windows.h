#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <ncurses.h>
class Logic;
class Window{
	public:
		Window();
		~Window();
		void draw(Logic* logic);
		void display(std::string text);
		void display(std::string text, int x, int y);
    void display(std::string text, int x, int y, WINDOW* window);
		void clearWindow();
    int getWidth(){ return width; }
    int getHeight(){ return height; }
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
