#include "config.h"
#include "message.h"
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "logic.h"
#include "utility.h"

int main(int argc, char* argv[]) {
#if defined(IS_UNIX) && defined(IS_DEBUG)
	std::cout << "Sleeping to allow attach" << std::endl;
	std::cout << getpid() << std::endl;
	std::cout << (IS_SFML ? "Starting in graphical mode" : "Starting in curses mode") << std::endl;
	sleep(1);
#endif
  Window window;
  srand(time(NULL)); 
  Logic logic(&window);
  window.setup(&logic);
  logic.init();

  while(logic.isRunning()){	
    window.clearWindow();
    logic.step();
    window.inputStep();
    window.debug("Time: " + SSTR(logic.getSecondsSinceStart()));
    window.draw();

#if !IS_SFML
		napms(TICK_LENGTH);
#endif
    logic.incrementTick();
  }

	window.destroy();
	logic.processMessages(); // Finish up messages
  std::cout << "Exiting game, thank you for playing!" << std::endl;
}
