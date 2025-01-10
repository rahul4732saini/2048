#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

void init_main_menu(WINDOW **window, Screen *screen)
{
    size_t height = main_menu_items_size + 2;
    size_t width = main_menu_width;

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
