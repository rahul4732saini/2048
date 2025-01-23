#ifndef _MENU_H
#define _MENU_H

#include <ncurses.h>
#include "shared.h"

void init_main_menu(Screen *scr, Screen *parent);
void init_pause_menu(Screen *scr, Screen *parent);

void show_main_menu(Screen *scr, size_t select, int select_color);
void show_pause_menu(Screen *scr, size_t select, int select_color);

#endif