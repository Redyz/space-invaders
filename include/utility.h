#ifndef UTILITY_H
#define UTILITY_H
#include <string>
//Macro from http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
#include <sstream>
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
    ( std::ostringstream() << std::dec << x ) ).str()
#define LOG_PATH "logs/logs.txt"

#ifdef IS_DEBUG
static bool DEBUG = true;
#else
static bool DEBUG = false;
#endif

class Window;
class Utility{
  public:
    Utility(Window *window);
    ~Utility();
    void print(std::string);
    void print(std::string, int x, int y);
		static bool directory_exists(std::string path);
		static int create_directory(std::string path);
  private:
    int log(std::string);

  public:

  private:
    Window *window;
};

class Logger{
  public:
    static void log(std::string message);
};


#endif
