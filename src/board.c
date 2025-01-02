#include <stdlib.h>
#include "shared.h"

cell_t **create_board(size_t size)
{
    cell_t **board = (cell_t **)malloc(size * sizeof(cell_t *));

    for (size_t i = 0; i < size; ++i)
    {
        board[i] = (cell_t *)calloc(size, sizeof(cell_t));
    }

    return board;
}

void free_board(cell_t **board, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        free(board[i]);

    free(board);
}