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

  //TODO: This should probably game.isRunning instead of logic
  //      considering the game can run without the logic
  while(logic.getGameState() != QUITTING){	
    window.clearWindow();
    if(logic.getGameState() == UNPAUSED)
      logic.step();
    auto time = Timer("Window");
    window.inputStep();
    window.debug("Time: " + SSTR(logic.getSecondsSinceStart()));
    window.draw();
    time.stop();
#if !IS_SFML
		napms(TICK_LENGTH);
#endif
    logic.incrementTick();
  }

	window.destroy();
	logic.processMessages(); // Finish up messages
  std::cout << "Exiting game, thank you for playing!" << std::endl;
}
