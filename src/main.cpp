#include "config.h"
#include "message.h"
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
int main(int argc, char* argv[]) {
#if defined(IS_UNIX) && defined(IS_DEBUG)
	std::cout << "Sleeping to allow attach" << std::endl;
	std::cout << getpid() << std::endl;
	sleep(1);
#endif
	std::cout << (IS_SFML ? "Starting in graphical mode" : "Starting in curses mode") << std::endl;
  Window window;
  srand(time(NULL)); 
  Logic logic(&window);
  window.setup(&logic);
  logic.init();

  while(logic.isRunning()){	
    window.clearWindow();
    logic.step();
    window.inputStep();
		window.debug("Test: " + SSTR(logic.getCurrentTick()));
    window.draw();
    usleep(1000 * TICK_LENGTH); //1000 milliseconds => 1 sec
    logic.incrementTick();
  }
	window.~Window(); // force destroy window
	logic.processMessages(); // Finish up messages
  std::cout << "Exiting game, thank you for playing!" << std::endl;
}
