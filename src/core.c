/*
 * @file core.c
 * @brief Defines handler functions for all game interface windows.
 *
 * This module defines functions for handling all the TUI windows
 * including user input management and integration of the logic associated
 * with the interface.
 */

#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>

#include "logic.h"
#include "shared.h"
#include "consts.h"

#include "interface/core.h"
#include "interface/board.h"
#include "interface/menu.h"

/*
 * @brief Handles the main menu interface window.
 *
 * This function displays the main menu window while handling user
 * input for triggering the actions  associated with the main menu
 * buttons.
 *
 * @param Pointer to the screens array comprising the Screen structs.
 * @return An integer code to indicate the pressed button signifying the
 *         action which needs to be triggered. The codes along with their
 *         actions are as follows:
 *         -  0 -> Start
 *         -  1 -> Exit
 *         - -1 -> Screen resize
 */
static int8_t handle_main_menu(Screen *scrs)
{
    int16_t input = 0;
    int8_t select = 0;

    place_main_menu(scrs + 2, scrs + 1);
    show_main_menu(scrs + 2, select, 1);

    // Displays the main menu window until the RETURN key is pressed
    // signifying a button press.
    while ((input = getch()) != 10)
    {
        switch (input)
        {
        case KEY_UP:
            --select;
            break;

        case KEY_DOWN:
            ++select;
            break;

        case KEY_RESIZE:
            return -1;
        }

        select = (select + main_menu_items_size) % main_menu_items_size;
        show_main_menu(scrs + 2, select, 1);
    }

    return select;
}

/*
 * @brief Handles the pause menu interface window.
 *
 * This function displays the pause menu window while handling user
 * input for triggering the actions  associated with the pause menu
 * buttons.
 *
 * @param Pointer to the screens array comprising the Screen structs.
 * @return An integer code to indicate the pressed button signifying the
 *         action which needs to be triggered. The codes along with their
 *         actions are as follows:
 *         -  0 -> Resume game
 *         -  1 -> Quit to main menu
 *         -  2 -> Quit game
 *         - -1 -> Screen resize
 */
static int8_t handle_pause_menu(Screen *scrs)
{
    int16_t input = 0;
    int8_t select = 0;

    place_pause_menu(scrs + 2, scrs + 1);
    show_pause_menu(scrs + 2, select, 1);

    // Displays the main menu window until the RETURN key is pressed
    // signifying a button press.
    while ((input = getch()) != 10)
    {
        switch (input)
        {
        case KEY_UP:
            --select;
            break;

        case KEY_DOWN:
            ++select;
            break;

        case KEY_RESIZE:
            return -1;
        }

        select = (select + pause_menu_items_size) % pause_menu_items_size;
        show_pause_menu(scrs + 2, select, 1);
    }

    return select;
}

/*
 * @brief Handles the game board interface window.
 *
 * This function displays the game board  window while handling the
 * complete 2048 game mechanics including user input management and
 * tile operations, placing random  values on the board, displaying
 * the game score and checking game over conditions at each move.
 *
 * @param scrs Pointers to the screens array comprising the Screen structs.
 * @param game Pointer to the Game struct comprising the game data.
 *
 * @return An integer code signifying the next action to be performed in
 *         the game session. The codes along with their actions associated
 *         are as follows:
 *         -  0 -> Game over (either won or lost)
 *         -  1 -> Open pause menu
 *         - -1 -> Screen resize
 */
static int8_t handle_game_board(Screen *scrs, Game *game)
{
    int16_t input, operations;
    bool iskey, isempty;

    static char score[20];

    place_board(scrs + 2, scrs + 1, game->bsize);
    show_board(scrs + 2, game);

    // Displays the current game score as the window title.
    sprintf(score, "Score: %zu", game->score);
    show_window_title(scrs + 1, score);

    // Displays the game board and handles the game mechanics
    // until the ESC key is pressed to open the pause menu.
    while ((input = getch()) != 27)
    {
        operations = 0;

        isempty = true;
        iskey = input == KEY_UP || input == KEY_LEFT;

        switch (input)
        {
        case KEY_UP:
        case KEY_DOWN:
            operations += add_vertical(game, iskey);
            operations += move_vertical(game, iskey);
            break;

        case KEY_LEFT:
        case KEY_RIGHT:
            operations += add_horizontal(game, iskey);
            operations += move_horizontal(game, iskey);
            break;

        case KEY_RESIZE:
            return -1;
        }

        if (operations)
            isempty = place_random(game);

        if (game_over(game, isempty) || game->max_val == target)
            return 0;

        // Updates the game score string and refreshes
        // the game board as well as the window title.

        sprintf(score, "Score: %zu", game->score);

        show_window_title(scrs + 1, score);
        show_board(scrs + 2, game);
    }

    return 1;
}

/*
 * @brief Handles the dialog box interface window.
 *
 * This function displays the dialog box window while handling user
 * input for triggering the actions associated with the dialog box
 * buttons.
 *
 * @param game_win Pointer to the game window screen.
 * @param mesg Pointer to the array comprising the strings to be displayed.
 * @param mesg_len Length of the mesg array.
 * @param select Integer signifying the color pair for the selected button.
 *
 * @return An integer code to indicate the pressed button signifying the
 *         action which needs to be triggered. The codes along with their
 *         actions are as follows:
 *         -  0 -> OK
 *         - -1 -> Screen resize
 */
static int8_t handle_dialog(Screen *game_win, const char *mesg[], size_t mesg_len, int select_color)
{
    show_dialog(game_win, mesg, mesg_len, select_color);

    int16_t input;

    // Displays the dialog box window until the RETURN
    // key is pressed signifying a button press.
    while ((input = getch()) != 10)
        if (input == KEY_RESIZE)
            return -1;

    return 0;
}

/*
 * @brief Sets up the Game struct for keeping track of
 *        the associated data during the game session.
 *
 * @return The Game struct comprising the inital game data.
 */
static Game setup_game(void)
{
    Game game;

    game.board = create_board(4);
    game.bsize = 4;
    game.max_val = game.score = 0;

    place_random(&game);
    place_random(&game);

    return game;
}

/*
 * @brief Cleans the dynamically allocated memory during initialization.
 * @param game Pointer to the Game struct comprising the game data.
 */
static void clean_game(Game *game)
{
    free_board(game);
}

/*
 * @brief Handles the 2048 game session.
 *
 * This function handles all the interface windows in the game, while
 * managing user input and, proper game setup and cleanup operations.
 *
 * @param scrs Pointer to the screens array comprising the Screen structs.
 *
 * @return An integer code signifying the next action to be performed
 *         in the game session. The codes along with their associated
 *         actions are as follows:
 *         -  0 -> Exit
 *         -  1 -> Restart
 */
int8_t handle_game(Screen *scrs)
{
    int8_t status;

    // Handles the main menu interface.
    do
        refresh_game_win(scrs + 1, scrs, main_menu_title);
    while ((status = handle_main_menu(scrs)) < 0);

    if (status == 1)
        return 0;

    // Sets up the Game struct and clears the window
    // title for displaying  the game score.
    Game game = setup_game();
    refresh_game_win(scrs + 1, scrs, "");

    // Handles the game board interface.
    while ((status = handle_game_board(scrs, &game)))
    {
        if (status < 0)
        {
            refresh_game_win(scrs + 1, scrs, "");
            continue;
        }

        // Handles the pause menu interface.
        do
            refresh_game_win(scrs + 1, scrs, pause_menu_title);
        while ((status = handle_pause_menu(scrs)) < 0);

        if (status == 1)
        {
            clean_game(&game);
            return 1;
        }

        else if (status == 2)
        {
            clean_game(&game);
            return 0;
        }

        refresh_game_win(scrs + 1, scrs, "");
    }

    refresh_game_win(scrs + 1, scrs, "");

    // Displays a dialog box based on whether
    // the end-user won or lost the game.
    if (game.max_val == target)
        handle_dialog(scrs + 1, win_dialog_txt, win_dialog_txt_len, 1);

    else
        handle_dialog(scrs + 1, lost_dialog_txt, lost_dialog_txt_len, 1);

    clean_game(&game);
    return 1;
}
