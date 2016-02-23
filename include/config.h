#ifndef CONFIG_H
#define CONFIG_H

#define IS_UNIX 1
/* #undef IS_NT */
#define IS_DEBUG 1

#define SFML true
#define TICK_LENGTH 40
#if SFML
  #include "gui/windows.h"
  #include "gui/input.h"
#else
  #include "guincurses/windows.h"
  #include "guincurses/input.h"
#endif
#endif


