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

void add_horizontal(Game *game, bool left)
{
    size_t start, end, last;
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
        last = game->bsize;

        for (size_t j = start; j != end; j += dir)
        {
            if (!game->board[i][j])
                continue;

            else if (last == game->bsize || game->board[i][j] != game->board[i][last])
            {
                last = j;
                continue;
            }

            game->board[i][last] *= 2;
            game->board[i][j] = 0;

            if (game->board[i][last] > game->max_val)
                game->max_val = game->board[i][last];

            game->score += game->board[i][last];

            last = game->bsize;
        }
    }
}

void add_vertical(Game *game, bool up)
{
    size_t start, end, last;
    int8_t dir = up ? 1 : -1;

    if (up)
    {
        start = 0, end = game->bsize;
    }
    else
    {
        start = game->bsize - 1, end = -1;
    }

    for (size_t i = 0; i < game->bsize; ++i)
    {
        last = game->bsize;

        for (size_t j = start; j != end; j += dir)
        {
            if (!game->board[j][i])
                continue;

            else if (last == game->bsize || game->board[j][i] != game->board[last][i])
            {
                last = j;
                continue;
            }

            game->board[last][i] *= 2;
            game->board[j][i] = 0;

            if (game->board[last][i] > game->max_val)
                game->max_val = game->board[last][i];

            game->score += game->board[last][i];

            last = game->bsize;
        }
    }
}

void move_horizontal(Game *game, bool left)
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

            j = (zindex += dir);
        }
    }
}

void move_vertical(Game *game, bool up)
{
    size_t start, end, zindex;
    int8_t dir = up ? 1 : -1;

    if (up)
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
            if (!game->board[j][i])
            {
                zindex = j;
                break;
            }
        }

        for (size_t j = zindex + dir; j != end; j += dir)
        {
            if (!game->board[j][i])
                continue;

            game->board[zindex][i] = game->board[j][i];
            game->board[j][i] = 0;

            j = (zindex += dir);
        }
    }
}

bool place_random(Game *game)
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

    return ctr > 1;
}

bool game_over(Game *game, bool cell_empty)
{
    if (cell_empty)
        return false;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        for (size_t j = 0; j < game->bsize - 1; ++j)
        {
            if (game->board[i][j] == game->board[i][j + 1] ||
                game->board[j][i] == game->board[j + 1][i])
                return false;
        }
    }

    return true;
}

void free_board(Game *game)
{
    for (size_t i = 0; i < game->bsize; ++i)
        free(game->board[i]);

    free(game->board);
}
