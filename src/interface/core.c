/**
 * @brief Defines core functions for handling the Text-based User Interface.
 *
 * This module defines functions for handling the core TUI functionalities
 * including the following:
 * - Initialzing the standard screen.
 * - Placing and displaying the game window.
 * - Displaying the window title, screen headers and footers.
 * - Displaying dialog windows.
 * - Refreshing the game window.
 */

#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

#include "interface/shared.h"

/**
 * @brief Initializes the standard TUI screen and sets up the
 * screen configuration.
 */
void init_screen()
{
    initscr();

    cbreak();
    noecho();
    start_color();

    curs_set(0);
    keypad(stdscr, TRUE);
}

/**
 * @brief Displays a dialog box at the center of the game window.
 *
 * This function defines mechanism to display a dialog box with the specified
 * message at the center of the game window, with an OK button displayed in the
 * specified selection color pair for accepting the text.
 *
 * @param scr Pointer to the Screen struct comprising the game window.
 * @param mesg Pointer to the array comprising the text as inidividual lines.
 * @param mesg_length Length of the mesg array.
 * @param select_color Integer signifying the color pair for marking selection.
 */
void show_dialog(Screen *scr, const char *mesg[], size_t mesg_len)
{
    Dimension *dim = scr->dimension;
    WINDOW *win = scr->window;

    // Calculates the current Y coordinates for placing the message.
    // A margin of 2 rows is reduced during the  calculation of the
    // centre position for the OK button.
    size_t cur_x, cur_y = (dim->height - mesg_len - 2) / 2;

    for (size_t i = 0; i < mesg_len; ++i)
    {
        // Calculates the left cutoff to place the text in the middle
        // of the game window.
        cur_x = (dim->width - strlen(mesg[i])) / 2;

        wmove(win, cur_y++, cur_x);
        wprintw(win, "%s", mesg[i]);
    }

    cur_x = (dim->width - dialog_bt_width) / 2;

    // Stores the internal left cutoff within the OK button
    // to place the text in the middle of the button.
    size_t inner_left_cutoff = (dialog_bt_width - strlen(dialog_bt_txt)) / 2;

    wmove(win, ++cur_y, cur_x);
    wattron(win, COLOR_PAIR(COLOR_SELECT));

    // Explicitly prints the left and right blank spaces
    // to display the foreground color within the button.

    wprintw(win, "%*s", inner_left_cutoff, "");
    wprintw(win, "%s", dialog_bt_txt);
    wprintw(win, "%*s", dialog_bt_width - inner_left_cutoff - strlen(dialog_bt_txt), "");

    wattroff(win, COLOR_PAIR(COLOR_SELECT));
    wrefresh(win);
}
