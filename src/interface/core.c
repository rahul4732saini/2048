/**
 * @brief Defines core functions for handling the TUI environment.
 *
 * @details This module defines functions for handling the core
 * TUI functionalities including standard screen initialization,
 * and displaying the end-game dialog box.
 */

#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

#include "interface/shared.h"

/**
 * @brief Initializes and configures the standard TUI screen.
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
void show_end_game_dialog(const char *mesg[], len_t mesg_len, Dimension *scr_dim)
{
    // Calculates the Y coordinates for placing the message. A margin of
    // 2 rows is reduced for the placement of the OK button in the center.
    pos_t pos_x, pos_y = (scr_dim->height - mesg_len - 2) / 2;

    for (index_t i = 0; i < mesg_len; ++i)
    {
        // Calculates the X coordinate to place the
        // text in the center of the TUI screen.
        pos_x = (scr_dim->width - strlen(mesg[i])) / 2;

        move(pos_y++, pos_x);
        printw("%s", mesg[i]);
    }

    pos_x = (scr_dim->width - dialog_bt_width) / 2;

    // The left cutoff is stored as a 32-bit signed integer to meet
    // the padding variable requirements for variadic formatting.

    len_t text_len = strlen(dialog_bt_txt);
    int left_cutoff = (dialog_bt_width - text_len) / 2;

    move(++pos_y, pos_x);
    attron(COLOR_PAIR(COLOR_SELECT));

    printw("%*s", left_cutoff, "");
    printw("%s", dialog_bt_txt);
    printw("%*s", dialog_bt_width - left_cutoff - text_len, "");

    attroff(COLOR_PAIR(COLOR_SELECT));
    refresh();
}
