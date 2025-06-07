#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "shared.h"

cell_t **create_board(void);
void free_board(cell_t **board);

void setup_game(Game *game);
bool is_game_over(Game *game, bool cell_empty);
bool place_random(Game *game);

bool add_horizontal(Game *game, bool to_right);
bool add_vertical(Game *game, bool to_bottom);

bool move_horizontal(Game *game, bool to_right);
bool move_vertical(Game *game, bool to_bottom);

#endif
