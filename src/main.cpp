#include <iostream>
#include <unistd.h>
#include <time.h>

#include "config.h"
#include "message.h"
#include "logic.h"
#include "utility.h"

#if !IS_SFML
#include <ncurses.h>
#endif

int main(void) {
#if IS_UTF8
  setlocale(LC_ALL, "");
#endif
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

  while(logic.getGameState() != QUITTING){
    window.clearWindow();
    if(logic.getGameState() == UNPAUSED)
      logic.step();
    auto time = Timer("Window");
    window.inputStep();
    window.draw();
    time.stop();
#if !IS_SFML
    napms(TICK_LENGTH);
#endif
    if(logic.getGameRunning())
      logic.incrementTick();
  }

  window.destroy();
  logic.processMessages(); // Finish up messages
  std::cout << "Exiting game, thank you for playing!" << std::endl;

#if IS_DEBUG
  sleep(100);
#endif
}
