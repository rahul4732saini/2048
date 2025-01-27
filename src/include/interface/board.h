#ifndef _INTERFACE_BOARD_H
#define _INTERFACE_BOARD_H

#include <ncurses.h>
#include "shared.h"

void place_board(Screen *scr, Screen *parent, size_t bsize);
void show_board(Screen *scr, Game *game);

#endif