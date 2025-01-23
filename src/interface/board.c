#include <math.h>
#include <ncurses.h>

#include "shared.h"
#include "consts.h"

void init_board(WINDOW **window, Screen *screen, size_t bsize)
{
    size_t height = bsize * 4 - 1 + 2;
    size_t width = bsize * 9 - 1 + 2;

    size_t start_y = (screen->height - height) / 2;
    size_t start_x = (screen->width - width) / 2;

    *window = newwin(
        height,
        width,
        screen->start_y + start_y,
        screen->start_x + start_x);

    refresh();

    keypad(*window, TRUE);
}

static void draw_vlines(WINDOW *window, size_t bsize)
{
    size_t y = getcury(window);

    for (size_t i = 0; i < cell_height; ++i)
    {
        wmove(window, y + i, 1);

        for (size_t j = 0; j < bsize - 1; ++j)
        {
            wprintw(window, "%*s", cell_width, "");
            waddch(window, ACS_VLINE);
        }
    }
}

static void draw_hlines(WINDOW *window, size_t bsize)
{
    for (size_t i = 0; i < bsize; ++i)
    {
        for (size_t j = 0; j < cell_width; ++j)
            waddch(window, ACS_HLINE);

        if (i != bsize - 1)
            waddch(window, ACS_PLUS);
    }
}

static void draw_edges(WINDOW *window, size_t bsize)
{
    size_t height = bsize * (cell_height + 1) + 1;
    size_t width = bsize * (cell_width + 1) + 1;

    for (size_t i = 1; i < bsize; ++i)
    {
        mvwaddch(window, 0, (cell_width + 1) * i, ACS_TTEE);
        mvwaddch(window, height - 1, (cell_width + 1) * i, ACS_BTEE);

        mvwaddch(window, (cell_height + 1) * i, 0, ACS_LTEE);
        mvwaddch(window, (cell_height + 1) * i, width - 1, ACS_RTEE);
    }
}

static void draw_grid(WINDOW *window, size_t bsize)
{
    draw_edges(window, bsize);

    for (size_t i = 0; i < bsize; ++i)
    {
        wmove(window, (cell_height + 1) * i + 1, 1);
        draw_vlines(window, bsize);

        if (i == bsize - 1)
            continue;

        wmove(window, (i + 1) * (cell_height + 1), 1);
        draw_hlines(window, bsize);
    }

    wrefresh(window);
}

static void populate_cells(WINDOW *window, Game *game)
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

            wmove(window, pos_y, pos_x);
            wprintw(window, "%d", game->board[i][j]);
        }
    }

    wrefresh(window);
}

void show_board(WINDOW *window, Game *game)
{
    size_t height = game->bsize * (cell_height + 1) + 1;
    size_t width = game->bsize * (cell_width + 1) + 1;

    box(window, 0, 0);
    wrefresh(window);

    draw_grid(window, game->bsize);
    populate_cells(window, game);
}
