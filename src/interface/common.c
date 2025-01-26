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

void place_window(Screen *scr)
{
    Dimension *dim = scr->dimension;

    wresize(scr->window, dim->height, dim->width);
    mvwin(scr->window, dim->start_y, dim->start_x);

    wclear(scr->window);
    wrefresh(scr->window);
}
