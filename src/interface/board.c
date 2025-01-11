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
