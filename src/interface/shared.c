#include <ncurses.h>
#include "shared.h"

WINDOW *init_window(void)
{
    WINDOW *win = newwin(0, 0, 0, 0);

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
