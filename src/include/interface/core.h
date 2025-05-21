#ifndef _INTERFACE_CORE_H
#define _INTERFACE_CORE_H

#include <ncurses.h>
#include "shared.h"

void init_screen();
void show_end_game_dialog(const char *mesg[], size_t mesg_len, Dimension *scr_dim);

#endif
