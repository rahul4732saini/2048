#ifndef _CORE_H
#define _CORE_H

#include <ncurses.h>
#include "shared.h"

void init_screen(Screen *scr);
void get_screen_dimension(Screen *scr);
void place_game_win(Screen *scr, Screen *parent);

void show_header_footer(Screen *scr);
void show_game_win(Screen *scr);
void show_window_title(Screen *scr, const char *title);

#endif
