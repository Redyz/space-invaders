#ifndef UTILITY_H
#define UTILITY_H
#include <string>
//Macro from http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
#include <sstream>
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
#define TICK_LENGTH 200
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
