#include "utility.h"
#include "config.h"
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>

#ifdef IS_NT
#include <direct.h>
#endif

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
	return 0;
}

bool Utility::directory_exists(std::string path){
	struct stat info;
	stat(path.c_str(), &info);
	if(info.st_mode & S_IFDIR)
		return true;
	return false;
}

// Returns 0 on success, 1 on error (path exists, can't create)
int Utility::create_directory(std::string path){
#ifdef IS_NT
	return mkdir(path.c_str()) == 0 ? 0 : 1;
#elif IS_UNIX
	return mkdir(path.c_str(), 0755) == 0 ? 0 : 1;
#endif
}

void Logger::log(std::string message){
  time_t currentTime = std::time(0); //now
  struct tm *currentTimeStruct = localtime(&currentTime);

	//TODO: constant
	if(!Utility::directory_exists("logs"))
		Utility::create_directory("logs");	

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
