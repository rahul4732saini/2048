/**
 * @brief Defines functions for handling the in-game menu windows.
 *
 * @details This module defines functions for initializing the displaying
 * the various in-game menu windows including the main and pause menu.
 */

#include <ncurses.h>
#include <string.h>

#include "shared.h"
#include "consts.h"

#include "interface/shared.h"

/**
 * @brief Displays the screen header and footer text comprising
 * general details about the game.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
static void show_header_footer(Dimension *scr_dim)
{
    // The header and footer text is placed with
    // 1 row of padding from the screen edges.

    for (index_t i = 0; i < headers_len; ++i)
    {
        move(i + 1, (scr_dim->width - strlen(headers[i])) / 2);
        printw("%s", headers[i]);
    }

    for (index_t i = 0; i < footers_len; ++i)
    {
        move(
            scr_dim->height - footers_len + i - 1,
            (scr_dim->width - strlen(footers[i])) / 2);

        printw("%s", footers[i]);
    }

    refresh();
}

/**
 * @brief Displays the specified menu heading on top on the
 * associated menu window.
 *
 * @param heading Text to be displayed on top on the menu window.
 * @param menu_start_y Vertical starting position of the menu.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
static inline void show_menu_heading(
    char *heading, size_t menu_start_y, Dimension *scr_dim)
{
    move(menu_start_y - 1, (scr_dim->width - strlen(heading)) / 2);
    printw("%s", heading);
}

/**
 * @brief Initializes the main menu and displays its
 * static layout on the TUI screen.
 *
 * @param wctx Pointer to the WinContext struct comprising the window data.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
void init_main_menu(WinContext *wctx, Dimension *scr_dim)
{
    Dimension *dim = wctx->dimension;

    dim->height = main_menu_option_cnt + 2;
    dim->width = main_menu_width;

    dim->start_y = (scr_dim->height - dim->height) / 2;
    dim->start_x = (scr_dim->width - dim->width) / 2;

    wctx->window = init_window(dim);

    box(wctx->window, 0, 0);
    show_menu_heading(main_menu_title, dim->start_y, scr_dim);
    show_header_footer(scr_dim);
}

/**
 * @brief Initializes the pause menu and displays its
 * static layout on the TUI screen.
 *
 * @param wctx Pointer to the WinContext struct comprising the window data.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
void init_pause_menu(WinContext *wctx, Dimension *scr_dim)
{
    Dimension *dim = wctx->dimension;

    dim->height = pause_menu_option_cnt + 2;
    dim->width = pause_menu_width;

    dim->start_y = (scr_dim->height - dim->height) / 2;
    dim->start_x = (scr_dim->width - dim->width) / 2;

    wctx->window = init_window(dim);

    box(wctx->window, 0, 0);
    show_menu_heading(pause_menu_title, dim->start_y, scr_dim);
    show_header_footer(scr_dim);
}

/**
 * @brief Displays the main menu window on the TUI screen.
 *
 * @details Displays the main menu window with the menu items
 * also highlighting the selected item marking the selection.
 *
 * @param wctx Pointer to the WinContext struct comprising the window data.
 * @param select Index of the selected menu item.
 */
void show_main_menu(WinContext *wctx, size_t select)
{
    WINDOW *win = wctx->window;

    // Left cutoff is stored as a 32-bit signed integer to meet
    // padding variable requirements in variadic formatting.

    int left_cutoff;
    len_t length, width = main_menu_width - 2;

    for (index_t i = 0; i < main_menu_option_cnt; ++i)
    {
        // Extracts the string length for cutoff calculation.
        length = strlen(main_menu_options[i]);
        left_cutoff = (width - length) / 2;

        // Configures the current background and foreground
        // color based on the index of the menu item.

        if (i == select)
            wattron(win, COLOR_PAIR(COLOR_SELECT));

        wmove(win, i + 1, 1);

        wprintw(win, "%*s", left_cutoff, "");
        wprintw(win, "%s", main_menu_options[i]);
        wprintw(win, "%*s", width - length - left_cutoff, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(COLOR_SELECT));
    }

    wrefresh(win);
}

/**
 * @brief Displays the pause menu window on the TUI screen.
 *
 * @details Displays the pause menu window with the menu items
 * also highlighting the selected item marking the selection.
 *
 * @param wctx Pointer to the WinContext struct comprising the window data.
 * @param select Index of the selected menu item.
 */
void show_pause_menu(WinContext *wctx, size_t select)
{
    WINDOW *win = wctx->window;

    // Left cutoff is stored as a 32-bit signed integer to meet
    // padding variable requirements in variadic formatting.

    int left_cutoff;
    len_t length, width = pause_menu_width - 2;

    for (index_t i = 0; i < pause_menu_option_cnt; ++i)
    {
        // Extracts string length for cutoff calculation.
        length = strlen(pause_menu_options[i]);
        left_cutoff = (width - length) / 2;

        // Configures the current background and foreground
        // color based on the index of the menu item.

        if (i == select)
            wattron(win, COLOR_PAIR(COLOR_SELECT));

        wmove(win, i + 1, 1);

        wprintw(win, "%*s", left_cutoff, "");
        wprintw(win, "%s", pause_menu_options[i]);
        wprintw(win, "%*s", width - length - left_cutoff, "");

        if (i == select)
            wattroff(win, COLOR_PAIR(COLOR_SELECT));
    }

    wrefresh(win);
}
