#ifndef _INTERFACE_CORE_H
#define _INTERFACE_CORE_H

#include <ncurses.h>
#include "shared.h"

void init_screen();
void show_dialog(Screen *scr, const char *mesg[], size_t mesg_len, int select_color);

#endif
