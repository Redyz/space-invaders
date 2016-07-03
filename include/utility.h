#pragma once

#include <string>
//Macro from http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
#include <sstream>
#include <cstdio>
#include <chrono>
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
    ( std::ostringstream() << std::dec << x ) ).str()
#define LOG_PATH "logs/logs.txt"

#define PPRINT( x, y ) printf("Adress of %s, 0%p\n", y, (void*)x);

class Window;
class Utility final{
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

class Timer final{
  public:
    Timer(std::string message);
    void stop();

  private:
    std::string message;
    std::chrono::high_resolution_clock::time_point start_time;
};

class Logger final{
  public:
    static void log(std::string message);
};
