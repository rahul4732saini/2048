#ifndef _CORE_H
#define _CORE_H

#include <ncurses.h>
#include "shared.h"

void init_screen(void);
void init_game_win(WINDOW **window, Screen *screen);
void display_header_footer(Screen *screen);
void show_window_title(WINDOW *window, Screen *screen, const char *title);

#endif
