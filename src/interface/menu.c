/**
 * @brief Defines functions for handling menu windows in the TUI.
 *
 * @details This module defines functions for placing and displaying
 *          the main and pause menu windows on the TUI screen.
 */

#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

/**
 * @brief Positions the main menu window on the TUI screen.
 *
 * @details Calculates the dimensions of the main menu window based
 *          on the dimensions of the game window and positions it on
 *          screen with the `place_window` function.
 *
 * @param scr Pointer to the Screen struct for the main menu.
 * @param parent Pointer to the Screen struct for the game window.
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

/**
 * @brief Positions the pause menu window on the TUI screen.
 *
 * @details Calculates the dimensions of the pause menu window based
 *          on the dimensions of the game window and positions it on
 *          screen with the `place_window` function.
 *
 * @param scr Pointer to the Screen struct for the pause menu.
 * @param parent Pointer to the Screen struct for the game window.
 */
void place_pause_menu(Screen *scr, Screen *parent)
{
    Dimension *dim_scr = scr->dimension, *dim_parent = parent->dimension;

    dim_scr->height = pause_menu_items_size + 2;
    dim_scr->width = pause_menu_width;

    dim_scr->start_y = dim_parent->start_y + (dim_parent->height - dim_scr->height) / 2;
    dim_scr->start_x = dim_parent->start_x + (dim_parent->width - dim_scr->width) / 2;

    place_window(scr);
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
