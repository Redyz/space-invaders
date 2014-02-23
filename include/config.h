#ifndef CONFIG_H
#define CONFIG_H

#define SFML false
#if SFML
	#include "gui/windows.h"
#else
	#include "guincurses/windows.h"
#endif
#endif


