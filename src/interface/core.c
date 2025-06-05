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

    // Reduced ESC key delay to 100ms to avoid performance issues.
    ESCDELAY = 100;

    curs_set(0);
    keypad(stdscr, TRUE);
}

/**
 * @brief Displays the end game dialog box.
 *
 * @details This functions displays the end game dialog box with
 * the specified message and an OK button for accepting the text.
 *
 * @param mesg Pointer to the array comprising the text as inidividual lines.
 * @param mesg_len Length of the message array.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 */
void show_end_game_dialog(const char *mesg[], size_t mesg_len, Dimension *scr_dim)
{
    // Calculates the Y coordinates for placing the message. A margin of
    // 2 rows is reduced for the placement of the OK button in the center.
    size_t pos_x, pos_y = (scr_dim->height - mesg_len - 2) / 2;

    for (size_t i = 0; i < mesg_len; ++i)
    {
        // Calculates the left cutoff to place the text in the center
        // of the TUI screen.
        pos_x = (scr_dim->width - strlen(mesg[i])) / 2;

        move(pos_y++, pos_x);
        printw("%s", mesg[i]);
    }

    pos_x = (scr_dim->width - dialog_bt_width) / 2;

    // Stores the internal left cutoff within the OK button
    // to place the text in the center of the button.
    size_t inner_left_cutoff = (dialog_bt_width - strlen(dialog_bt_txt)) / 2;

    move(++pos_y, pos_x);
    attron(COLOR_PAIR(COLOR_SELECT));

    printw("%*s", inner_left_cutoff, "");
    printw("%s", dialog_bt_txt);
    printw("%*s", dialog_bt_width - inner_left_cutoff - strlen(dialog_bt_txt), "");

    attroff(COLOR_PAIR(COLOR_SELECT));
    refresh();
}
