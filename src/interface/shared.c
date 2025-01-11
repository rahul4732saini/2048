#include <ncurses.h>
#include "shared.h"

void init_window(WINDOW **window, Screen *screen)
{
    *window = newwin(
        screen->height,
        screen->width,
        screen->start_y,
        screen->start_x);

    keypad(*window, TRUE);
    refresh();
}
