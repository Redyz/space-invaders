#ifndef WINDOW_H
#define WINDOW_H
#include <string>

class Window{
	public:
		Window();
		~Window();
		void draw();
		void display(std::string text);
		void display(std::string text, int x, int y);
	private:
		int width;
		int height;

};

#endif
