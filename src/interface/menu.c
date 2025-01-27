#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

#include "interface/common.h"

void place_main_menu(Screen *scr, Screen *parent)
{
    Dimension *dim_scr = scr->dimension, *dim_parent = parent->dimension;

    dim_scr->height = main_menu_items_size + 2;
    dim_scr->width = main_menu_width;

    dim_scr->start_y = (dim_parent->height - dim_scr->height) / 2;
    dim_scr->start_x = (dim_parent->width - dim_scr->width) / 2;

    place_window(scr);
}

void show_main_menu(Screen *scr, size_t select, int select_color)
{
    WINDOW *win = scr->window;
    box(win, 0, 0);

    size_t width = main_menu_width - 2;
    size_t length, left_cut, right_cut;

    for (size_t i = 0; i < main_menu_items_size; ++i)
    {
        length = strlen(main_menu_items[i]);

        left_cut = (width - length) / 2;
        right_cut = width - length - left_cut;

        if (i == select)
            wattron(win, COLOR_PAIR(select_color));

        wmove(win, i + 1, 1);

        wprintw(win, "%*s", left_cut, "");
        wprintw(win, "%s", main_menu_items[i]);
        wprintw(win, "%*s", right_cut, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(select_color));
    }

    wrefresh(win);
}

void place_pause_menu(Screen *scr, Screen *parent)
{
    Dimension *dim_scr = scr->dimension, *dim_parent = parent->dimension;

    dim_scr->height = pause_menu_items_size + 2;
    dim_scr->width = pause_menu_width;

    dim_scr->start_y = (dim_parent->height - dim_scr->height) / 2;
    dim_scr->start_x = (dim_parent->width - dim_scr->width) / 2;

    place_window(scr);
}

void show_pause_menu(Screen *scr, size_t select, int select_color)
{
    WINDOW *win = scr->window;
    box(win, 0, 0);

    size_t width = pause_menu_width - 2;
    size_t length, left_cut, right_cut;

    for (size_t i = 0; i < pause_menu_items_size; ++i)
    {
        length = strlen(pause_menu_items[i]);

        left_cut = (width - length) / 2;
        right_cut = width - length - left_cut;

        if (i == select)
            wattron(win, COLOR_PAIR(select_color));

        wmove(win, i + 1, 1);

        wprintw(win, "%*s", left_cut, "");
        wprintw(win, "%s", pause_menu_items[i]);
        wprintw(win, "%*s", right_cut, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(select_color));
    }

    wrefresh(win);
}
