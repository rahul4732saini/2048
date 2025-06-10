/**
 * @file shared.c
 * @brief Defines shared functions for common TUI routines.
 *
 * @details This module defines common utility functions
 * required by TUI handler functions within other modules.
 */

#include <ncurses.h>
#include "shared.h"

/**
 * @brief Initializes and configures a new ncurses TUI window.
 * @param dim Pointer to the Dimension struct comprising the window dimensions.
 * @return Pointer to the newly created window.
 */
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
