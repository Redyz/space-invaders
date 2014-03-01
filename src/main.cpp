#include "config.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <unistd.h>
#include <time.h>
#include "logic.h"
#include "utility.h"

#if SFML
	#include "gui/windows.h"
#else
	#include "guincurses/windows.h"
#endif
using namespace std;

int main(int argc, char* argv[]) {
	int currentTick = 0;
	cout << (SFML ? "Starting in graphical mode" : "Starting in curses mode") << endl;
	Window window;
  srand(time(NULL)); //new seed
	Logic logic(&window);
  window.setup(&logic);
	bool running = true;
  logic.init();
	while(running){	
    window.clearWindow();
		logic.step();
		window.draw();
		window.display("Howdy folks");
		currentTick++;
		usleep(1000 * TICK_LENGTH); //1000 milliseconds => 1 sec
	}
}

////cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

//sf::Window screen(sf::VideoMode(800, 600), "myproject");
//bool running = true;
//while (running) {
//  screen.display();
//}

	
