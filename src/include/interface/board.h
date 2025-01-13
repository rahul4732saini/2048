#ifndef _INTERFACE_BOARD_H
#define _INTERFACE_BOARD_H

#include <ncurses.h>
#include "shared.h"

void init_board(WINDOW **window, Screen *screen, size_t bsize);
void show_board(WINDOW *window, Game *game);

#endif