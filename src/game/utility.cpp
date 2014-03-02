#include "utility.h"
#include "config.h"
#include <string>

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
