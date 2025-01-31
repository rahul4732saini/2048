#ifndef _CORE_H
#define _CORE_H

#include "shared.h"

int8_t handle_main_menu(Screen *scrs);
int8_t handle_pause_menu(Screen *scrs);
int8_t handle_game_board(Screen *scrs, Game *game);

#endif