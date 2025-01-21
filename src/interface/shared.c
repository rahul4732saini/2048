#include <ncurses.h>
#include "shared.h"

WINDOW *init_window(Dimension *dim)
{
    WINDOW *win = newwin(
        dim->height,
        dim->width,
        dim->start_y,
        dim->start_x);

    refresh();
    keypad(win, TRUE);

    return win;
}
