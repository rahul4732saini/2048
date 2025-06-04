#ifndef _INTERFACE_BOARD_H
#define _INTERFACE_BOARD_H

#include <ncurses.h>
#include "shared.h"

void init_game_win(WinContext *wctx, Dimension *scr_dim);
void show_board(WinContext *wctx, Game *game);

#endif