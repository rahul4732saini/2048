/**
 * @brief Defines functions for handling the game board window.
 *
 * @details This module defines functions for initializing and
 * displaying the game board on the TUI screen.
 */

#include <math.h>
#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

/**
 * @brief Draws the vertical grid lines.
 * @param win Pointer to the game board window.
 */
static void draw_vlines(WINDOW *win)
{
    for (index_t i = 0; i < BOARD_SIZE; ++i)
        for (pos_t j = 1; j < BOARD_SIZE * (CELL_HEIGHT + 1); ++j)
            mvwaddch(win, j, i * (CELL_WIDTH + 1), ACS_VLINE);
}

/**
 * @brief Draws the horizontal grid line for an individual row.
 * @param win Pointer to the game board window.
 */
static void draw_hline(WINDOW *win)
{
    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (index_t _ = 0; _ < CELL_WIDTH; ++_)
            waddch(win, ACS_HLINE);

        // Draws a '+' symbol at the intersection of the vertical
        // and horizontal grid lines for visual appeal.
        if (i != BOARD_SIZE - 1)
            waddch(win, ACS_PLUS);
    }
}

/**
 * @brief Draws the edges of the horizontal and vertical grid lines.
 *
 * @details Draws the 'T' symbol rotated in appropriate directions to mark
 * the edges of the horizontal and vertical grid lines on the game board.
 *
 * @param win Pointer to the game board window.
 */
static void draw_edges(WINDOW *win)
{
    // Draws the edges for individual horizontal and vertical lines.
    for (index_t i = 1; i < BOARD_SIZE; ++i)
    {
        // Draws the edges for the vertical grid line.
        mvwaddch(win, 0, (CELL_WIDTH + 1) * i, ACS_TTEE);
        mvwaddch(win, BOARD_HEIGHT - 1, (CELL_WIDTH + 1) * i, ACS_BTEE);

        // Draws the edges for the horizontal grid line.
        mvwaddch(win, (CELL_HEIGHT + 1) * i, 0, ACS_LTEE);
        mvwaddch(win, (CELL_HEIGHT + 1) * i, BOARD_WIDTH - 1, ACS_RTEE);
    }
}

/**
 * @brief Draws the game board grid layout.
 *
 * @param win Pointer to the game board window.
 * @param bsize Size of the game board.
 */
static void draw_grid(WINDOW *win)
{
    box(win, 0, 0);

    draw_edges(win);
    draw_vlines(win);

    // Draws individual horizontal grid lines for each row of cells.
    for (index_t i = 1; i < BOARD_SIZE; ++i)
    {
        wmove(win, i * (CELL_HEIGHT + 1), 1);
        draw_hline(win);
    }

    wrefresh(win);
}

/**
 * @brief Populate the cells with their corresponding values on the game board.
 *
 * @param win Pointer to the game board window.
 * @param game Pointer to the Game struct comprising the game data.
 */
static void populate_cells(WINDOW *win, Game *game)
{
    pos_t pos_x, pos_y;
    len_t num_len;

    wattron(win, A_BOLD);

    for (index_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (index_t j = 0; j < BOARD_SIZE; ++j)
        {
            // Calculates the X and Y coordinates for value placement.
            pos_x = j * (CELL_WIDTH + 1) + 1;
            pos_y = i * (CELL_HEIGHT + 1) + CELL_HEIGHT / 2 + 1;

            // Clears the middle row of the cell to remove any
            // previously placed value.
            wmove(win, pos_y, pos_x);
            wprintw(win, "%*s", CELL_WIDTH, "");

            if (!game->board[i][j])
                continue;

            // Calculates the length of the number to place it
            // in the center of the cell.
            num_len = floor(log10(game->board[i][j])) + 1;

            wmove(win, pos_y, pos_x + (CELL_WIDTH - num_len) / 2);
            wprintw(win, "%d", game->board[i][j]);
        }
    }

    wattroff(win, A_BOLD);
    wrefresh(win);
}

/**
 * @brief Displays the game score at the bottom of the screen.
 *
 * @param score The score to be displayed.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
static void show_game_score(score_t score, Dimension *scr_dim)
{
    char string[20];
    snprintf(string, sizeof(string), "Score: %u", score);

    move(scr_dim->height - 2, (scr_dim->width - strlen(string)) / 2);
    printw("%s", string);

    refresh();
}

/**
 * @brief Initializes the game window and displays its
 * static layout on the TUI screen.
 *
 * @param wctx Pointer to the WinContxet struct comprising the window data.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
void init_game_win(WinContext *wctx, Dimension *scr_dim)
{
    Dimension *dim = wctx->dimension;

    *dim = (Dimension){
        BOARD_HEIGHT,
        BOARD_WIDTH,
        (scr_dim->height - BOARD_HEIGHT) / 2,
        (scr_dim->width - BOARD_WIDTH) / 2,
    };

    wctx->window = init_window(dim);
    draw_grid(wctx->window);
}

/**
 * @brief Displays the game window on the TUI screen.
 *
 * @details Refreshes the dynamic content of the game window by
 * updating the board cells and displaying the current game score.
 *
 * @param wctx Pointer to the WinContext struct comprising window data.
 * @param game Pointer to the Game struct comrising the game data.
 */
void show_board(WinContext *wctx, Game *game, Dimension *scr_dim)
{
    populate_cells(wctx->window, game);
    show_game_score(game->score, scr_dim);
}
