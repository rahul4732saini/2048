/**
 * @file logic.c
 * @brief Defines functions for handling the core game logic.
 *
 * @details This module defines functions for handling the logical
 * components of the game including tile operations and game board
 * management.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "logic.h"
#include "shared.h"
#include "consts.h"

/**
 * @brief Dynamically allocates memory for the game board.
 * @return Pointer to the game board.
 */
cell_t **create_board(void)
{
    cell_t **board = (cell_t **)malloc(BOARD_SIZE * sizeof(cell_t *));

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        board[i] = (cell_t *)calloc(BOARD_SIZE, sizeof(cell_t));
    }

    return board;
}

/**
 * @brief Frees the dynamically allocated memory for the game board.
 * @param board Pointer to the game board.
 */
void free_board(cell_t **board)
{
    for (index_t i = 0; i < BOARD_SIZE; ++i)
        free(board[i]);

    free(board);
}

/**
 * @brief Sets up the Game struct for a new game session.
 *
 * @details Resets all the cells on the game board to 0, place 2 random
 * values for the initial state, sets init to true and resets the other
 * variables to their defaults.
 *
 * @param game Pointer to the Game struct comprising the game data.
 */
void setup_game(Game *game)
{
    for (index_t i = 0; i < BOARD_SIZE; ++i)
        memset(game->board[i], 0, BOARD_SIZE * sizeof(cell_t));

    place_random(game);
    place_random(game);

    game->max_val = 2, game->score = 0;
    game->init = true;
}

/**
 * @brief Horizontally adds tiles based on the specified direction.
 *
 * @details Adds and merges adjacent equal tiles horizontally in the
 * specified direction (left/right), and updates the game metadata.
 *
 * @param game Pointer to the Game struct comprising all the game data.
 * @param to_left Boolean value to indicate whether to perform the
 * operation from right to left or left to right.
 *
 * @return Boolean value indicating whether any operations were performed.
 */
bool add_horizontal(Game *game, bool to_left)
{
    index_t start, end, last;
    index_t dir = to_left ? 1 : -1;

    bool operated = false;

    // The following conditional statements define the starting and
    // ending index for the operation based on the speciifed direction.

    if (to_left)
        start = 0, end = BOARD_SIZE;

    else
        start = BOARD_SIZE - 1, end = -1;

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        // -1 is used as a special value to signify unavailability
        // of a compatible cell for operation.
        last = -1;

        for (index_t j = start; j != end; j += dir)
        {
            if (!game->board[i][j])
                continue;

            else if (last == -1 || game->board[i][j] != game->board[i][last])
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
            last = -1;

            operated = true;
        }
    }

    return operated;
}

/**
 * @brief Vertically adds tiles based on the specified direction.
 *
 * @details Adds and merges adjacent equal tiles vertically in the
 * specified direction (top/down), and updates the game metadata.
 *
 * @param game Pointer to the Game struct comprising the game data.
 * @param to_top Boolean value to indicate whether to perform the
 * operation from bottom to top or from top to bottom.
 *
 * @return Boolean value indicating whether any operations were performed.
 */
bool add_vertical(Game *game, bool to_top)
{
    index_t start, end, last;
    index_t dir = to_top ? 1 : -1;

    bool operated = false;

    // The following conditional statements define the starting and
    // ending index for the operation based on the specified direction.

    if (to_top)
        start = 0, end = BOARD_SIZE;

    else
        start = BOARD_SIZE - 1, end = -1;

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        // -1 is used as a special value to signify unavailability
        // of a compatible cell for operation.
        last = -1;

        for (index_t j = start; j != end; j += dir)
        {
            if (!game->board[j][i])
                continue;

            else if (last == -1 || game->board[j][i] != game->board[last][i])
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
            last = -1;

            operated = true;
        }
    }

    return operated;
}

/**
 * @brief Horizontally moves tiles based on the specified direction.
 *
 * @param game Pointer to the Game struct comprising the game data.
 * @param to_left Boolean value to indicate whether to perform
 * the operation from right to left or from left to right.
 *
 * @return Boolean value indicating whether any operations were performed.
 */
bool move_horizontal(Game *game, bool to_left)
{
    index_t start, end, inx_0;
    index_t dir = to_left ? 1 : -1;

    bool operated = false;

    // The following conditional statements defined the starting and
    // ending index for the operation based on the specified direction.

    if (to_left)
        start = 0, end = BOARD_SIZE;

    else
        start = BOARD_SIZE - 1, end = -1;

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        // -1 is used as a special value to indicate the absence
        // of empty tiles before the current position.
        inx_0 = -1;

        for (index_t j = start; j != end; j += dir)
        {
            if (game->board[i][j] && inx_0 != -1)
            {
                // Swaps the tiles, updates the operations counter and updates
                // inx_0 by 1 in the direction of operation as the next tile is
                // always meant to be zero.

                game->board[i][inx_0] = game->board[i][j];
                game->board[i][j] = 0;

                inx_0 += dir;
                operated = true;
            }

            else if (!game->board[i][j] && inx_0 == -1)
                inx_0 = j;
        }
    }

    return operated;
}

/**
 * @brief Vertically moves the tiles based on the specified direction.
 *
 * @param game Pointer to the Game struct comprising the game data.
 * @param to_top Boolean value to indicate whether to perform
 * the operation from bottom to top or from top to bottom.
 *
 * @return Boolean value indicating whether any operations were performed.
 */
bool move_vertical(Game *game, bool to_top)
{
    index_t start, end, inx_0;
    index_t dir = to_top ? 1 : -1;

    bool operated = false;

    // The following conditional statements define the starting and
    // ending index for the operation absed on the specified direction.

    if (to_top)
        start = 0, end = BOARD_SIZE;

    else
        start = BOARD_SIZE - 1, end = -1;

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        // -1 is used as a special value to indicate the absence
        // of empty tiles before the current position.
        inx_0 = -1;

        for (index_t j = start; j != end; j += dir)
        {
            if (game->board[j][i] && inx_0 != -1)
            {
                // Swaps the tiles, updates the operations counter and updates
                // "inx_0" by 1 in the direction of operation as the subsequent
                // tile is always meant to be zero.

                game->board[inx_0][i] = game->board[j][i];
                game->board[j][i] = 0;

                inx_0 += dir;
                operated = true;
            }

            else if (!game->board[j][i] && inx_0 == -1)
                inx_0 = j;
        }
    }

    return operated;
}

/**
 * @brief Randomly places the value 2 at an empty tile on the game board.
 * @param game Pointer to the Game struct comprising the game data.
 *
 * @return Boolean value signifying the presence of empty
 * tiles after the value has been placed on the game board.
 */
bool place_random(Game *game)
{
    index_t positions[BOARD_SIZE * BOARD_SIZE];
    index_t ctr = 0;

    // Searches for empty tiles on the game board and adds
    // their positions in the array for random selection.

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (index_t j = 0; j < BOARD_SIZE; ++j)
        {
            if (game->board[i][j])
                continue;

            positions[ctr++] = i * BOARD_SIZE + j;
        }
    }

    if (!ctr)
        return false;

    index_t pos = positions[rand() % ctr];
    game->board[pos / BOARD_SIZE][pos % BOARD_SIZE] = 2;

    return ctr > 1;
}

/**
 * @brief Checks if the game is over.
 *
 * @param game Pointer to the Game struct comprising the game data.
 * @param cell_empty Whether there is any empty cell on the
 * game board, to indicate that the game is still not over.
 *
 * @return Boolean value signifying whether the game is over.
 */
bool is_game_over(Game *game, bool cell_empty)
{
    if (cell_empty)
        return false;

    // Iterates though the game board looking up for equal
    // adjacent tiles to check if the game is still not over.

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (index_t j = 0; j < BOARD_SIZE - 1; ++j)
        {
            if (game->board[i][j] == game->board[i][j + 1] ||
                game->board[j][i] == game->board[j + 1][i])
                return false;
        }
    }

    return true;
}
