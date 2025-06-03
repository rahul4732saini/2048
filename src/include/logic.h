#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "shared.h"

cell_t **create_board(void);
void free_board(cell_t **board);

bool is_game_over(Game *game, bool cell_empty);
bool place_random(Game *game);

size_t add_horizontal(Game *game, bool to_right);
size_t add_vertical(Game *game, bool to_bottom);

size_t move_horizontal(Game *game, bool to_right);
size_t move_vertical(Game *game, bool to_bottom);

#endif
