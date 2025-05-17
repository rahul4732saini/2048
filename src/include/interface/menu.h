#ifndef _MENU_H
#define _MENU_H

#include <ncurses.h>
#include "shared.h"

void init_main_menu(WinContext *wctx, Dimension *scr_dim);
void show_main_menu(WinContext *wctx, size_t select);

void init_pause_menu(WinContext *wctx, Dimension *scr_dim);
void show_pause_menu(WinContext *wctx, size_t select);

#endif
