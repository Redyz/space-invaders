#include "utility.h"
#include "config.h"
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

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
  logFile.open(LOG_PATH, std::ios::out | std::fstream::app);
  if(!logFile.is_open()){
    std::cout << "Could not open log file! Cowardly exiting!" << std::endl;
    std::exit(0);
  }
  strftime(buffer, sizeof(buffer), "[%Y-%m-%d][%X] ", currentTimeStruct);
  logFile << buffer << message << std::endl; 
  logFile.close();
  //
}
