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
    size_t y, _;
    getyx(window, y, _);

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
