//#include "config.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <unistd.h>
#include "logic.h"
using namespace std;

int main(int argc, char* argv[]) {
////cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

//sf::Window screen(sf::VideoMode(800, 600), "myproject");
//bool running = true;
//while (running) {
//  screen.display();
//}

	
	//Logic *logic = new Logic();
	Logic logic;
	bool running = true;
	while(running){
		usleep(1000 * 1000); //1000 milliseconds => 1 sec
		logic.step();
		cout << "Hello" << endl;
	}
}
