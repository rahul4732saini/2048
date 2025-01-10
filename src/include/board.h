#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "shared.h"

cell_t **create_board(size_t size);
void add_horizontal(Game *game, bool left);
void add_vertical(Game *game, bool left);
void move_horizontal(Game *game, bool left);
void move_vertical(Game *game, bool left);
bool place_random(Game *game);
void free_board(Game *game);

#endif
