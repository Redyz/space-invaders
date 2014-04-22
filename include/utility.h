#ifndef UTILITY_H
#define UTILITY_H
#include <string>
//Macro from http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
#include <sstream>
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
    ( std::ostringstream() << std::dec << x ) ).str()
#define LOG_PATH "logs/logs.txt"
//this ^ might be ugly - probably need to revise this part
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

class Logger{
  public:
    static void log(std::string message);
};

#endif

//#include "unistd.h"
//#include "stdio.h"
//char currentPath[FILENAME_MAX];
//cout << getcwd(currentPath, sizeof(currentPath));
//return 0;
