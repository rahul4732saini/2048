#ifndef _INTERFACE_SHARED_H
#define _INTERFACE_SHARED_H

#include <ncurses.h>
#include "shared.h"

WINDOW *init_window(Dimension *dim);
void place_window(Screen *scr);

#endif