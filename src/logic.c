/**
 * @file logic.c
 * @brief Implements all logical aspects of the 2048 game.
 *
 * This module defines functions for handling all game logic
 * including the following:
 * - Handling tile movement and merge operations.
 * - Defintion and decomposition of the game board.
 * - Checking game status conditions.
 * - Placing values randomly on the game board.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "shared.h"

/**
 * @brief Dynamically allocates memory for the game board.
 * @return Pointer to the game board.
 */
cell_t **create_board(void)
{
    cell_t **board = (cell_t **)malloc(BOARD_SIZE * sizeof(cell_t *));

    for (size_t i = 0; i < BOARD_SIZE; ++i)
    {
        board[i] = (cell_t *)calloc(BOARD_SIZE, sizeof(cell_t));
    }

    return board;
}

/**
 * @brief Horizontally merges tiles based on the specified direction.
 *
 * @param game Pointer to the game structure comprising the game board.
 * @param left This parameter is used for identifying the direction of
 *             the addition operation. A boolean true signifies a left
 *             to right operation whereas the other signifies a right to
 *             left operation.
 *
 * @return Total number of addition operations performed.
 */
size_t add_horizontal(Game *game, bool left)
{
    size_t start, end, last, operations = 0;
    int8_t dir = left ? 1 : -1;

    // The following conditional statements define the starting
    // and ending indices for the addition operation based on the
    // specified direction of operation.

    if (left)
        start = 0, end = game->bsize;

    else
        start = game->bsize - 1, end = -1;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        // assigns the game board size to last signfying that there is
        // no compatible cell for merging on the right or left based on
        // the direction.
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

            // Updates the maximum tile value, game score and the operations
            // counter. Also resets the last variable to signify incompatibility.

            if (game->board[i][last] > game->max_val)
                game->max_val = game->board[i][last];

            game->score += game->board[i][last];
            last = game->bsize;

            ++operations;
        }
    }

    return operations;
}

/**
 * @brief Vertically merges tiles based on the specified direction.
 *
 * @param game Pointer to the game structure comprising the game board.
 * @param up Signifies the direction of the addition operation. A boolean
 *           true signifies a top to bottom operation whereas the other
 *           signifies a bottom to top operation.
 *
 * @return Total number of addition operations performed.
 */
size_t add_vertical(Game *game, bool up)
{
    size_t start, end, last, operations = 0;
    int8_t dir = up ? 1 : -1;

    // The following conditional statements define the starting
    // and ending indices for the addition operation based on the
    // specified direction of operation.

    if (up)
        start = 0, end = game->bsize;

    else
        start = game->bsize - 1, end = -1;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        // assigns the game board size to last signfying that there is
        // no compatible cell for merging on the top or bottom based on
        // the direction.
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

            // Updates the maximum tile value, game score and the operations
            // counter. Also resets the last variable to signify incompatibility.

            game->board[last][i] *= 2;
            game->board[j][i] = 0;

            if (game->board[last][i] > game->max_val)
                game->max_val = game->board[last][i];

            game->score += game->board[last][i];
            last = game->bsize;

            ++operations;
        }
    }

    return operations;
}

/**
 * @brief Horizontally moves tiles based on the specified direction.
 *
 * @param game Pointer to the Game structure comprising the game board.
 * @param left Signifies the direction of the movement operation. A boolean
 *             true signifies a left to right operation whereas the other
 *             signifies a right to left operation.
 *
 * @return Total number of movement operations performed.
 */
size_t move_horizontal(Game *game, bool left)
{
    size_t start, end, zindex, operations = 0;
    int8_t dir = left ? 1 : -1;

    // The following conditional statements define the starting
    // and ending indices for the movement operation based on the
    // specified direction of operation.

    if (left)
        start = 0, end = game->bsize;

    else
        start = game->bsize - 1, end = -1;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        // assigns the game board size to last signfying that there is
        // no zero cell on the left or right based on the direction.
        zindex = game->bsize;

        for (size_t j = start; j != end; j += dir)
        {
            if (game->board[i][j] && zindex != game->bsize)
            {
                // Swaps the tiles, updates the operations counter and increments
                // zindex by 1 in the operation direction as the next tile is
                // always meant to be a zero in the current scenario.

                game->board[i][zindex] = game->board[i][j];
                game->board[i][j] = 0;

                zindex += dir;
                ++operations;
            }

            else if (!game->board[i][j] && zindex == game->bsize)
                zindex = j;
        }
    }

    return operations;
}

/**
 * @brief Vertically moves tiles based on the specified direction.
 *
 * @param game Pointer to the Game structure comprising the game board.
 * @param up Signifies the direction of the movement operation. A boolean
 *           true signifies a top to bottom operation whereas the other
 *           signifies a bottom to top operation.
 *
 * @return Total number of movement operations performed.
 */
size_t move_vertical(Game *game, bool up)
{
    size_t start, end, zindex, operations = 0;
    int8_t dir = up ? 1 : -1;

    // The following conditional statements define the starting
    // and ending indices for the movement operation based on the
    // specified direction of operation.

    if (up)
        start = 0, end = game->bsize;

    else
        start = game->bsize - 1, end = -1;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        // assigns the game board size to last signfying that there is
        // no zero cell on the left or right based on the direction.
        zindex = game->bsize;

        for (size_t j = start; j != end; j += dir)
        {
            if (game->board[j][i] && zindex != game->bsize)
            {
                // Swaps the tiles, updates the operations counter and increments
                // zindex by 1 in the operation direction as the next tile is
                // always meant to be a zero in the current scenario.

                game->board[zindex][i] = game->board[j][i];
                game->board[j][i] = 0;

                zindex += dir;
                ++operations;
            }

            else if (!game->board[j][i] && zindex == game->bsize)
                zindex = j;
        }
    }

    return operations;
}

/**
 * @brief Places the value 2 at a random tile on the game board.
 * @param game Pointer to the Game structure comprising the game board.
 * @return A boolean value signifying the presence of empty tiles.
 */
bool place_random(Game *game)
{
    size_t positions[game->bsize * game->bsize];
    size_t ctr = 0;

    // Iterates through all the tiles and appends the indices to the
    // positions array for random selection.

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

/**
 * @brief Checks if the game is over and the player has lost.
 *
 * @param game Pointer to the game structure comprising the game board.
 * @param cell_empty Whether there are any empty cells on the game board.
 *
 * @return A Boolean value signifying whether the game is over.
 */
bool game_over(Game *game, bool cell_empty)
{
    if (cell_empty)
        return false;

    // Iterates though the game board looking up for equal
    // adjacent tiles to check if the game is still not over.
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

/**
 * @brief Frees the dynamically allocated memory for the game board.
 * @param game Pointer to the Game structure comprising the game board.
 */
void free_board(Game *game)
{
    for (size_t i = 0; i < game->bsize; ++i)
        free(game->board[i]);

    free(game->board);
}
