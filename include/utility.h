#ifndef UTILITY_H
#define UTILITY_H
#include <string>
class Window;
class Utility{
	public:
		Utility(Window *window);
		~Utility();
		void print(std::string);
		void print(std::string, int x, int y);
	private:
		int log(std::string);

	public:
		
	private:
		Window *window;
};

#endif
