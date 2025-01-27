#ifndef _INTERFACE_SHARED_H
#define _INTERFACE_SHARED_H

#include <ncurses.h>
#include "shared.h"

WINDOW *init_window(void);
void place_window(Screen *scr);

#endif