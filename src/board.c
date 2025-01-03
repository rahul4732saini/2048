#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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

void move_horizontal(struct Game *game, bool left)
{
    size_t start, end, zindex;
    int8_t dir = left ? 1 : -1;

    if (left)
    {
        start = 0, end = game->bsize;
    }
    else
    {
        start = game->bsize - 1, end = -1;
    }

    for (size_t i = 0; i < game->bsize; ++i)
    {
        zindex = end - dir;

        for (size_t j = start; j != end; j += dir)
        {
            if (!game->board[i][j])
            {
                zindex = j;
                break;
            }
        }

        for (size_t j = zindex + dir; j != end; j += dir)
        {
            if (!game->board[i][j])
                continue;

            game->board[i][zindex] = game->board[i][j];
            game->board[i][j] = 0;

            j = (zindex += dir) + dir;
        }
    }
}

bool place_random(struct Game *game)
{
    size_t positions[game->bsize * game->bsize];
    size_t ctr = 0;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        for (size_t j = 0; j < game->bsize; ++j)
        {
            if (game->board[i][j])
                continue;

            positions[ctr++] = i * game->bsize + j;
        }
    }

    if (!ctr)
        return false;

    size_t position = positions[rand() % ctr];
    game->board[position / game->bsize][position % game->bsize] = 2;

    return true;
}

void free_board(struct Game *game)
{
    for (size_t i = 0; i < game->bsize; ++i)
        free(game->board[i]);

    free(game->board);
}