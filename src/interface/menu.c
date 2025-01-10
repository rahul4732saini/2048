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

void show_main_menu(WINDOW *window, size_t select, int select_color)
{
    box(window, 0, 0);

    size_t width = main_menu_width - 2;
    size_t length, left_cut, right_cut;

    for (size_t i = 0; i < main_menu_items_size; ++i)
    {
        length = strlen(main_menu_items[i]);

        left_cut = (width - length) / 2;
        right_cut = width - length - left_cut;

        if (i == select)
            wattron(window, COLOR_PAIR(select_color));

        wmove(window, i + 1, 1);
        wprintw(window, "%*s%s%*s", left_cut, "", main_menu_items[i], right_cut, "");

        if (i == select)
            wattroff(window, COLOR_PAIR(select_color));
    }

    wrefresh(window);
}

void init_pause_menu(WINDOW **window, Screen *screen)
{
    size_t height = pause_menu_items_size + 2;
    size_t width = pause_menu_width;

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
