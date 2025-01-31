#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "shared.h"

cell_t **create_board(size_t size);
void free_board(Game *game);

bool game_over(Game *game, bool cell_empty);
bool place_random(Game *game);

size_t add_horizontal(Game *game, bool left);
size_t add_vertical(Game *game, bool up);

size_t move_horizontal(Game *game, bool left);
size_t move_vertical(Game *game, bool up);

#endif
