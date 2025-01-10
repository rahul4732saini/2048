#ifndef _MENU_H
#define _MENU_H

#include <ncurses.h>
#include "shared.h"

void init_main_menu(WINDOW **window, Screen *screen);
void init_pause_menu(WINDOW **window, Screen *screen);

void show_main_menu(WINDOW *window, size_t select, int select_color);
void show_pause_menu(WINDOW *window, size_t select, int select_color);

#endif