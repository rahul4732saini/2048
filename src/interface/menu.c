/**
 * @brief Defines functions for handling menu interfaces.
 *
 * This function defines the functions for placing and
 * displaying the main and pause menu interfaces.
 */

#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

/**
 * @brief Places the main menu on the screen based on the
 * Dimension structs within the specified Screen structs.
 *
 * This functions calculates the dimensions of the main menu
 * window and transform it with the `place_window` function.
 *
 * @param scr Screen struct comprising the main menu window data.
 * @param parent Screen struct comprising the game window data.
 */
void place_main_menu(Screen *scr, Screen *parent)
{
    Dimension *dim_scr = scr->dimension, *dim_parent = parent->dimension;

    dim_scr->height = main_menu_items_size + 2;
    dim_scr->width = main_menu_width;

    dim_scr->start_y = dim_parent->start_y + (dim_parent->height - dim_scr->height) / 2;
    dim_scr->start_x = dim_parent->start_x + (dim_parent->width - dim_scr->width) / 2;

    place_window(scr);
}

void show_main_menu(Screen *scr, size_t select, int select_color)
{
    WINDOW *win = scr->window;
    box(win, 0, 0);

    size_t width = main_menu_width - 2;
    size_t length, left_cutoff;

    for (size_t i = 0; i < main_menu_items_size; ++i)
    {
        length = strlen(main_menu_items[i]);
        left_cutoff = (width - length) / 2;

        if (i == select)
            wattron(win, COLOR_PAIR(select_color));

        wmove(win, i + 1, 1);

        wprintw(win, "%*s", left_cutoff, "");
        wprintw(win, "%s", main_menu_items[i]);
        wprintw(win, "%*s", width - length - left_cutoff, "");

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

    dim_scr->start_y = dim_parent->start_y + (dim_parent->height - dim_scr->height) / 2;
    dim_scr->start_x = dim_parent->start_x + (dim_parent->width - dim_scr->width) / 2;

    place_window(scr);
}

void show_pause_menu(Screen *scr, size_t select, int select_color)
{
    WINDOW *win = scr->window;
    box(win, 0, 0);

    size_t width = pause_menu_width - 2;
    size_t length, left_cutoff;

    for (size_t i = 0; i < pause_menu_items_size; ++i)
    {
        length = strlen(pause_menu_items[i]);
        left_cutoff = (width - length) / 2;

        if (i == select)
            wattron(win, COLOR_PAIR(select_color));

        wmove(win, i + 1, 1);

        wprintw(win, "%*s", left_cutoff, "");
        wprintw(win, "%s", pause_menu_items[i]);
        wprintw(win, "%*s", width - length - left_cutoff, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(select_color));
    }

    wrefresh(win);
}
