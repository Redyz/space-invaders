#include "config.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <unistd.h>
#include "logic.h"

#if SFML
	#include "gui/windows.h"
#else
	#include "guincurses/windows.h"
#endif
using namespace std;

int main(int argc, char* argv[]) {
	int currentTick = 0;
	cout << (SFML ? "Starting in graphical mode" : "Starting in curses mode") << endl;
	Logic logic;
	Window window;
	bool running = true;
	while(running){	
		logic.step();
		//window.draw();
		cout << "Hello" << currentTick << endl;
		currentTick++;
		usleep(1000 * 1000); //1000 milliseconds => 1 sec
	}
}

////cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

//sf::Window screen(sf::VideoMode(800, 600), "myproject");
//bool running = true;
//while (running) {
//  screen.display();
//}

	
