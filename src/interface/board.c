/**
 * @brief Defines functions for handling the 2048 game board interface.
 *
 * This module defines functions for placing and
 * displaying the 2048 game board on the TUI screen.
 */

#include <math.h>
#include <ncurses.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

void init_game_win(Screen *scr, size_t bsize)
{
    Dimension *dim = scr->dimension;

    dim->height = bsize * (cell_height + 1) + 1;
    dim->width = bsize * (cell_width + 1) + 1;

    dim->start_y = (getmaxy(stdscr) - dim->height) / 2;
    dim->start_x = (getmaxx(stdscr) - dim->width) / 2;

    scr->window = init_window(dim);
}

/**
 * @brief Draws vertical grid lines on the game board.
 *
 * @param win Pointer to the game board window.
 * @param bsize Size of the game board.
 */
static void draw_vlines(WINDOW *win, size_t bsize)
{
    for (size_t i = 1; i < bsize * (cell_height + 1); ++i)
    {
        wmove(win, i, 1);

        for (size_t j = 0; j < bsize - 1; ++j)
        {
            wprintw(win, "%*s", cell_width, "");
            waddch(win, ACS_VLINE);
        }
    }
}

/**
 * @brief Draws horizontal grid line for an individual row on the game board.
 *
 * @param win Pointer to the game board window.
 * @param bsize Size of the game board.
 */
static void draw_hline(WINDOW *win, size_t bsize)
{
    for (size_t i = 0; i < bsize; ++i)
    {
        for (size_t j = 0; j < cell_width; ++j)
            waddch(win, ACS_HLINE);

        // Draws a '+' symbol at the intersection of the vertical
        // and horizontal grid lines for visual appeal.
        if (i != bsize - 1)
            waddch(win, ACS_PLUS);
    }
}

/**
 * @brief Draws the edges of the horizontal and
 *        vertical grid lines on the game board.
 *
 * @details Draws the 'T' symbol rotated in a favourable direction to mark the
 *          edges of the horizontal and vertical grid lines on the game board.
 *
 * @param win Pointer to the game board window.
 * @param bsize Size of the game board.
 */
static void draw_edges(WINDOW *win, size_t bsize)
{
    size_t height = bsize * (cell_height + 1) + 1;
    size_t width = bsize * (cell_width + 1) + 1;

    // Draws the edges for each individual horizontal and vertical line.
    for (size_t i = 1; i < bsize; ++i)
    {
        // Draws the edges of the vertical grid line.
        mvwaddch(win, 0, (cell_width + 1) * i, ACS_TTEE);
        mvwaddch(win, height - 1, (cell_width + 1) * i, ACS_BTEE);

        // Draws the edges of the horizontal grid line.
        mvwaddch(win, (cell_height + 1) * i, 0, ACS_LTEE);
        mvwaddch(win, (cell_height + 1) * i, width - 1, ACS_RTEE);
    }
}

/**
 * @brief Draws the 2048 game board grid within the associated TUI window.
 *
 * @param win Pointer to the game board window.
 * @param bsize Size of the game board.
 */
static void draw_grid(WINDOW *win, size_t bsize)
{
    box(win, 0, 0);

    draw_edges(win, bsize);
    draw_vlines(win, bsize);

    // Draws horizontal lines vertically between all individual
    // cells on the game board.
    for (size_t i = 0; i < bsize - 1; ++i)
    {
        wmove(win, (i + 1) * (cell_height + 1), 1);
        draw_hline(win, bsize);
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
    size_t pos_x, pos_y, num_len;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        for (size_t j = 0; j < game->bsize; ++j)
        {
            if (!game->board[i][j])
                continue;

            // Calculates the length of the number to place it
            // at the center of the cell.
            num_len = floor(log10(game->board[i][j])) + 1;

            // Calculates the X and Y coordinates for placing the value.
            pos_x = j * (cell_width + 1) + (cell_width - num_len) / 2 + 1;
            pos_y = i * (cell_height + 1) + cell_height / 2 + 1;

            wmove(win, pos_y, pos_x);
            wprintw(win, "%d", game->board[i][j]);
        }
    }

    wrefresh(win);
}

/**
 * @brief Displays the game score at the bottom of the screen.
 * @param score The score to be displayed.
 */
void show_game_score(size_t score)
{
    char string[20];
    snprintf(string, sizeof(string), "Score: %d", string);

    size_t height = getmaxy(stdscr), width = getmaxx(stdscr);

    move(height - 2, (width - strlen(string)) / 2);
    printw("%s", string);
}

/**
 * @brief Displays the game board window on the TUI screen.
 *
 * @details Draws the game board in the associated window and
 *          populates the cells with their associated values.
 *
 * @param scr Pointer to the Screen struct comprising the game board window data.
 * @param game Pointer to the Game struct comrising the game data.
 */
void show_board(Screen *scr, Game *game)
{
    WINDOW *win = scr->window;

    wclear(win);

    draw_grid(win, game->bsize);
    populate_cells(win, game);
}
