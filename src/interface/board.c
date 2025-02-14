#include <math.h>
#include <ncurses.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

void place_board(Screen *scr, Screen *parent, size_t bsize)
{
    Dimension *dim_scr = scr->dimension, *dim_pr = parent->dimension;

    dim_scr->height = bsize * (cell_height + 1) + 1;
    dim_scr->width = bsize * (cell_width + 1) + 1;

    dim_scr->start_y = dim_pr->start_y + (dim_pr->height - dim_scr->height) / 2;
    dim_scr->start_x = dim_pr->start_x + (dim_pr->width - dim_scr->width) / 2;

    place_window(scr);
}

static void draw_vlines(WINDOW *win, size_t bsize)
{
    size_t y = getcury(win);

    for (size_t i = 0; i < cell_height; ++i)
    {
        wmove(win, y + i, 1);

        for (size_t j = 0; j < bsize - 1; ++j)
        {
            wprintw(win, "%*s", cell_width, "");
            waddch(win, ACS_VLINE);
        }
    }
}

static void draw_hlines(WINDOW *win, size_t bsize)
{
    for (size_t i = 0; i < bsize; ++i)
    {
        for (size_t j = 0; j < cell_width; ++j)
            waddch(win, ACS_HLINE);

        if (i != bsize - 1)
            waddch(win, ACS_PLUS);
    }
}

static void draw_edges(WINDOW *win, size_t bsize)
{
    size_t height = bsize * (cell_height + 1) + 1;
    size_t width = bsize * (cell_width + 1) + 1;

    for (size_t i = 1; i < bsize; ++i)
    {
        mvwaddch(win, 0, (cell_width + 1) * i, ACS_TTEE);
        mvwaddch(win, height - 1, (cell_width + 1) * i, ACS_BTEE);

        mvwaddch(win, (cell_height + 1) * i, 0, ACS_LTEE);
        mvwaddch(win, (cell_height + 1) * i, width - 1, ACS_RTEE);
    }
}

static void draw_grid(WINDOW *win, size_t bsize)
{
    draw_edges(win, bsize);

    for (size_t i = 0; i < bsize; ++i)
    {
        wmove(win, (cell_height + 1) * i + 1, 1);
        draw_vlines(win, bsize);

        if (i == bsize - 1)
            continue;

        wmove(win, (i + 1) * (cell_height + 1), 1);
        draw_hlines(win, bsize);
    }

    wrefresh(win);
}

static void populate_cells(WINDOW *win, Game *game)
{
    size_t pos_x, pos_y, num_len;

    for (size_t i = 0; i < game->bsize; ++i)
    {
        for (size_t j = 0; j < game->bsize; ++j)
        {
            if (!game->board[i][j])
                continue;

            num_len = floor(log10(game->board[i][j])) + 1;

            pos_x = j * (cell_width + 1) + (cell_width - num_len) / 2 + 1;
            pos_y = i * (cell_height + 1) + cell_height / 2 + 1;

            wmove(win, pos_y, pos_x);
            wprintw(win, "%d", game->board[i][j]);
        }
    }

    wrefresh(win);
}

void show_board(Screen *scr, Game *game)
{
    WINDOW *win = scr->window;

    wclear(win);

    box(win, 0, 0);
    wrefresh(win);

    draw_grid(win, game->bsize);
    populate_cells(win, game);
}
