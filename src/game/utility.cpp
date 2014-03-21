#include "utility.h"
#include "config.h"
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdio.h>

Utility::Utility(Window *window){
  this->window = window;
}

Utility::~Utility(){

}

void Utility::print(std::string text){
  window->display(text);
}

void Utility::print(std::string text, int x, int y){
  window->display(text, x, y);
}

int Utility::log(std::string){

}

void Logger::log(std::string message){
  time_t currentTime = std::time(0); //now
  struct tm *currentTimeStruct = localtime(&currentTime);
  char buffer[100];
  std::fstream logFile;
  logFile.open(LOG_PATH, std::fstream::out | std::fstream::ate | std::fstream::app);
  //logFile << "[" << (currentTimeStruct->tm_year + 1900) <<
    //"-" << (currentTimeStruct->tm_mon + 1) << "-" << (currentTimeStruct->tm_mday) << "] " << message << std::endl;
  strftime(buffer, sizeof(buffer), "[%Y-%m-%d][%X] ", currentTimeStruct);
  logFile << buffer << message << std::endl; 
  logFile.close();
}
