/**
 * @brief Defines functions for handling the in-game menu interfaces.
 *
 * @details This module defines functions for initializing the displaying
 * the various in-game menu interfaces including the main and pause menu.
 */

#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

void init_main_menu(Screen *scr)
{
    Dimension *dim = scr->dimension;

    dim->height = main_menu_items_size + 2;
    dim->width = main_menu_width;

    dim->start_y = (getmaxy(stdscr) - dim->height) / 2;
    dim->start_x = (getmaxx(stdscr) - dim->width) / 2;

    scr->window = init_window(dim);
}

/**
 * @brief Displays the main menu window on the TUI screen.
 *
 * @details Displays the main menu window with the menu items also highlighting
 *          the selected item in the specified color pair marking the selection.
 *
 * @param scr Pointer to the Screen struct for the main menu.
 * @param select Index of the selected menu item.
 * @param select_color Integer signifying the color pair for marking selection.
 */
void show_main_menu(Screen *scr, size_t select, int select_color)
{
    WINDOW *win = scr->window;
    box(win, 0, 0);

    size_t width = main_menu_width - 2;
    size_t length, left_cutoff;

    for (size_t i = 0; i < main_menu_items_size; ++i)
    {
        // Extracts the length of the string and calculates the size
        // of the left cutoff to display it at the center of the menu.
        length = strlen(main_menu_items[i]);
        left_cutoff = (width - length) / 2;

        // Configures the current background and foreground
        // color based on the index of the menu item.

        if (i == select)
            wattron(win, COLOR_PAIR(select_color));

        wmove(win, i + 1, 1);

        // Explicitly prints the left and right blank spaces to display
        // the foreground color in case the current item is selected.

        wprintw(win, "%*s", left_cutoff, "");
        wprintw(win, "%s", main_menu_items[i]);
        wprintw(win, "%*s", width - length - left_cutoff, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(select_color));
    }

    wrefresh(win);
}

void init_pause_menu(Screen *scr, Dimension *scr_dim)
{
    Dimension *dim = scr->dimension;

    dim->height = pause_menu_items_size + 2;
    dim->width = pause_menu_width;

    dim->start_y = (scr_dim->height - dim->height) / 2;
    dim->start_x = (scr_dim->width - dim->width) / 2;

    scr->window = init_window(dim);
}

/**
 * @brief Displays the pause menu window on the TUI screen.
 *
 * @details Displays the pause menu window with the menu items also highlighting
 *          the selected item in the specified color pair marking the selection.
 *
 * @param scr Pointer to the Screen struct for the pause menu.
 * @param select Index of the selected menu item.
 * @param select_color Integer signifying the color pair for marking selection.
 */
void show_pause_menu(Screen *scr, size_t select, int select_color)
{
    WINDOW *win = scr->window;
    box(win, 0, 0);

    size_t width = pause_menu_width - 2;
    size_t length, left_cutoff;

    for (size_t i = 0; i < pause_menu_items_size; ++i)
    {
        // Extracts the length of the string and calculates the size
        // of the left cutoff to display it at the center of the menu.
        length = strlen(pause_menu_items[i]);
        left_cutoff = (width - length) / 2;

        // Configures the current background and foreground
        // color based on the index of the menu item.

        if (i == select)
            wattron(win, COLOR_PAIR(select_color));

        wmove(win, i + 1, 1);

        // Explicitly prints the left and right blank spaces to display
        // the foreground color in case the current item is selected.

        wprintw(win, "%*s", left_cutoff, "");
        wprintw(win, "%s", pause_menu_items[i]);
        wprintw(win, "%*s", width - length - left_cutoff, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(select_color));
    }

    wrefresh(win);
}
