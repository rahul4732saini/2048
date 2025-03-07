#ifndef _INTERFACE_CORE_H
#define _INTERFACE_CORE_H

#include <ncurses.h>
#include "shared.h"

void init_screen(Screen *scr);
void get_screen_dimension(Screen *scr);
void place_game_win(Screen *scr, Screen *parent);

void show_header_footer(Screen *scr);
void show_game_win(Screen *scr);
void show_window_title(Screen *scr, const char *title);
void show_dialog(Screen *scr, const char *mesg[], size_t mesg_len, int select_color);

void refresh_game_win(Screen *game_scr, Screen *core_scr, const char *title);

#endif
