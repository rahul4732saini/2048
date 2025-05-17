/**
 * @file shared.c
 * @brief Defines shared functions for common TUI routines.
 *
 * @details This module defines functions used for performing actions common
 *          to and reuiqred by all the TUI handler functions defined within
 *          other modules.
 */

#include <ncurses.h>
#include "shared.h"

/**
 * @brief Initializes and configures a new ncurses TUI window.
 * @return Pointer to the newly created window.
 */
WINDOW *init_window(void)
{
    WINDOW *win = newwin(0, 0, 0, 0);

    refresh();
    keypad(win, TRUE);

    return win;
}
