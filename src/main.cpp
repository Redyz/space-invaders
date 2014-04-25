#include "config.h"
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "logic.h"
#include "utility.h"

#if SFML
	#include "gui/windows.h"
#else
	#include "guincurses/windows.h"
#endif

/**
 TODO: Pass messages through a queue first
 */
using namespace std;

int main(int argc, char* argv[]) {
  cout << (SFML ? "Starting in graphical mode" : "Starting in curses mode") << endl;
  Window window;
  srand(time(NULL)); //new seed
  Logic logic(&window);
  window.setup(&logic);
  logic.init();
  while(logic.isRunning()){	
    window.clearWindow();
    logic.step();
    window.inputStep();
    window.draw();
    usleep(1000 * TICK_LENGTH); //1000 milliseconds => 1 sec
    logic.incrementTick();
  }
  std::cout << "Exiting game, thank you for playing!" << std::endl;
}

////cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

//sf::Window screen(sf::VideoMode(800, 600), "myproject");
//bool running = true;
//while (running) {
//  screen.display();
//}

	
