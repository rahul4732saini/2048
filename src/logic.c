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
#include "consts.h"

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
 * @brief Horizontally adds tiles based on the specified direction.
 *
 * @details Adds and merges adjacent equal tiles in all rows across
 * the game board in the given direction (left/right), and updates
 * the game metadata.
 *
 * @param game Pointer to the Game struct comprising all the game data.
 * @param to_right Boolean value to indicate whether to perform a left to
 * right operation. If false, the operation is performed right to left.
 *
 * @return Total number of addition operations performed.
 */
size_t add_horizontal(Game *game, bool to_right)
{
    size_t start, end, last, operations = 0;
    int8_t dir = to_right ? 1 : -1;

    // The following conditional statements define the starting and
    // ending index for the operation based on the speciifed direction.

    if (to_right)
        start = 0, end = BOARD_SIZE;

    else
        start = BOARD_SIZE - 1, end = -1;

    for (size_t i = 0; i < BOARD_SIZE; ++i)
    {
        // The board size is used as a special index to signify
        // unavailability of a compatible cell for operation.
        last = BOARD_SIZE;

        for (size_t j = start; j != end; j += dir)
        {
            if (!game->board[i][j])
                continue;

            else if (last == BOARD_SIZE || game->board[i][j] != game->board[i][last])
            {
                last = j;
                continue;
            }

            game->board[i][last] *= 2;
            game->board[i][j] = 0;

            // Updates the game metadata and operations counter, and
            // resets the "last" variable to signify unavailability.

            if (game->board[i][last] > game->max_val)
                game->max_val = game->board[i][last];

            game->score += game->board[i][last];
            last = BOARD_SIZE;

            ++operations;
        }
    }

    return operations;
}

/**
 * @brief Vertically adds tiles based on the specified direction.
 *
 * @details Adds and merges adjacent equal tiles in all columns
 * across the game board in the specified direction (top/down),
 * and updates the game metadata.
 *
 * @param game Pointer to the Game struct comprising the game data.
 * @param to_bottom Boolean value to indicate whether to perform a top to
 * bottom operation. If false, the operation is performed bottom to top.
 *
 * @return Total number of addition operations performed.
 */
size_t add_vertical(Game *game, bool to_bottom)
{
    size_t start, end, last, operations = 0;
    int8_t dir = to_bottom ? 1 : -1;

    // The following conditional statements define the starting and
    // ending index for the operation based on the specified direction.

    if (to_bottom)
        start = 0, end = BOARD_SIZE;

    else
        start = BOARD_SIZE - 1, end = -1;

    for (size_t i = 0; i < BOARD_SIZE; ++i)
    {
        // The board size is used as a special index to signify
        // unavailability of a compatible cell for operation.
        last = BOARD_SIZE;

        for (size_t j = start; j != end; j += dir)
        {
            if (!game->board[j][i])
                continue;

            else if (last == BOARD_SIZE || game->board[j][i] != game->board[last][i])
            {
                last = j;
                continue;
            }

            // Updates the game metadata and operations counter, and
            // resets the "last" variable to signify unavailability.

            game->board[last][i] *= 2;
            game->board[j][i] = 0;

            if (game->board[last][i] > game->max_val)
                game->max_val = game->board[last][i];

            game->score += game->board[last][i];
            last = BOARD_SIZE;

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
    size_t positions[BOARD_SIZE * BOARD_SIZE];
    size_t ctr = 0;

    // Iterates through all the tiles and appends the indices to the
    // positions array for random selection.

    for (size_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (size_t j = 0; j < BOARD_SIZE; ++j)
        {
            if (game->board[i][j])
                continue;

            positions[ctr++] = i * BOARD_SIZE + j;
        }
    }

    if (!ctr)
        return false;

    size_t pos = positions[rand() % ctr];
    game->board[pos / BOARD_SIZE][pos % BOARD_SIZE] = 2;

    return ctr > 1;
}

/**
 * @brief Checks if the game is over and the player has lost.
 *
 * @param board Pointer to the game board.
 * @param cell_empty Whether there is any empty cell on the game board.
 *
 * @return A Boolean value signifying whether the game is over.
 */
bool is_game_over(cell_t **board, bool cell_empty)
{
    if (cell_empty)
        return false;

    // Iterates though the game board looking up for equal
    // adjacent tiles to check if the game is still not over.
    for (size_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (size_t j = 0; j < BOARD_SIZE - 1; ++j)
        {
            if (board[i][j] == board[i][j + 1] ||
                board[j][i] == board[j + 1][i])
                return false;
        }
    }

    return true;
}

/**
 * @brief Frees the dynamically allocated memory for the game board.
 * @param board Pointer to the game board.
 */
void free_board(cell_t **board)
{
    for (size_t i = 0; i < BOARD_SIZE; ++i)
        free(board[i]);

    free(board);
}
