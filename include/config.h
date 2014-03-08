#ifndef CONFIG_H
#define CONFIG_H

#define SFML false
#define TICK_LENGTH 40
#if SFML
  #include "gui/windows.h"
  #include "gui/input.h"
#else
  #include "guincurses/windows.h"
  #include "guincurses/input.h"
#endif
#endif


