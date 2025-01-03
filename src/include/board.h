#ifndef _BOARD_H
#define _BOARD_H

#include "shared.h"

cell_t **create_board(size_t size);
void free_board(struct Game *game);

#endif
