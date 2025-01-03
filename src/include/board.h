#ifndef _BOARD_H
#define _BOARD_H

#include <stdbool.h>
#include "shared.h"

cell_t **create_board(size_t size);
void add_horizontal(struct Game *game, bool left);
void move_horizontal(struct Game *game, bool left);
void move_vertical(struct Game *game, bool left);
bool place_random(struct Game *game);
void free_board(struct Game *game);

#endif
