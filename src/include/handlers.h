#ifndef _CORE_H
#define _CORE_H

#include "shared.h"

extern Game game;

handler_t handle_main_menu(Dimension *scr_dim);
handler_t handle_pause_menu(Dimension *scr_dim);
handler_t handle_game_board(Dimension *scr_dim);
handler_t handle_end_game_dialog(Dimension *scr_dim);

#endif