#ifndef _CORE_H
#define _CORE_H

#include "shared.h"

void init_screen(void);
void init_game_win(WINDOW **window, struct Screen *screen);
void display_header_footer(struct Screen *screen);

#endif
