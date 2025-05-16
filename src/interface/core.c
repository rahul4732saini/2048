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
 * @brief Initializes the standard screen and sets up the screen configurations.
 * @param scr Pointer to the Screen struct comprising the standard screen data.
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
 * @brief Extracts the standard screen dimensions and stores them in the
 *        Dimension struct within the specified Screen struct.
 *
 * @param scr Pointer to the Screen struct comprising the standard screen data.
 */
void get_screen_dimension(Screen *scr)
{
    Dimension *dim = scr->dimension;

    dim->start_x = dim->start_y = 0;
    getmaxyx(stdscr, dim->height, dim->width);
}

/**
 * @brief Places the game window on the screen based on the
 *        dimensions stored in Dimension structs within the
 *        specified Screen structs.
 *
 * This functions calculates the dimensions of the game window
 * and transform it with the `place_window` function.
 *
 * @param scr Screen struct comprising the game window data.
 * @param parent Screen struct comprising the standard screen data.
 */
void place_game_win(Screen *scr, Screen *parent)
{
    Dimension *dim_scr = scr->dimension, *dim_parent = parent->dimension;

    dim_scr->width = dim_parent->width - win_horizontal_margins;
    dim_scr->height = dim_parent->height - win_vertical_margins;

    dim_scr->start_x = win_horizontal_margins / 2;
    dim_scr->start_y = win_vertical_margins / 2;

    place_window(scr);
}

/**
 * @brief Displays the screen header and footer text.
 *
 * Displays the header and footer text above and below the game window
 * providing general details about the game and its associates.
 *
 * @param scr Pointer to the Screen struct comprising the standard screen data.
 */
void show_header_footer(Screen *scr)
{
    Dimension *dim = scr->dimension;

    // Stores the left cutoff to place the text at the center of the game window.
    size_t st_pos;

    // Places the headers below the game window with
    // a 1 row padding above and below the text.
    for (size_t i = 0; i < headers_len; ++i)
    {
        st_pos = (dim->width - strlen(headers[i])) / 2;
        mvprintw(1 + i, st_pos, "%s", headers[i]);
    }

    // Places the footers below the game window with
    // a 1 row padding above and below the text.
    for (size_t i = 0; i < footers_len; ++i)
    {
        st_pos = (dim->width - strlen(footers[i])) / 2;
        mvprintw(dim->height - footers_len + i - 1, st_pos, "%s", footers[i]);
    }

    wrefresh(scr->window);
}

/**
 * @brief Displays the game window on the TUI screen.
 * @param scr Screen struct comprising the game window data.
 */
void show_game_win(Screen *scr)
{
    box(scr->window, 0, 0);
    wrefresh(scr->window);
}

/**
 * @brief Displays the window title on the top of the game window.
 *
 * @param scr Pointer to the Screen struct comprising the game window data.
 * @param title The text to be displayed as the window title.
 */
void show_window_title(Screen *scr, const char *title)
{
    size_t start_x = (scr->dimension->width - strlen(title)) / 2;

    mvwprintw(scr->window, 2, start_x, "%s", title);
    wrefresh(scr->window);
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
void show_dialog(Screen *scr, const char *mesg[], size_t mesg_len, int select_color)
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
    wattron(win, COLOR_PAIR(select_color));

    // Explicitly prints the left and right blank spaces
    // to display the foreground color within the button.

    wprintw(win, "%*s", inner_left_cutoff, "");
    wprintw(win, "%s", dialog_bt_txt);
    wprintw(win, "%*s", dialog_bt_width - inner_left_cutoff - strlen(dialog_bt_txt), "");

    wattroff(win, COLOR_PAIR(select_color));
    wrefresh(win);
}
