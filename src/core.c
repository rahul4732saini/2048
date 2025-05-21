/**
 * @file core.c
 * @brief Defines functions for handling in-game interfaces.
 *
 * @details This module defines handler functions for all in-game TUI
 * interfaces, including user input management and integration of the
 * logic associated with them.
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

Game game;

/**
 * @brief Handles the specified in-game menu interface.
 *
 * @details This function displays the specified menu window and handles
 * user input for triggering the actions associated with the menu buttons.
 *
 * @param menu Pointer to the Menu struct comprising the menu details.
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
static size_t handle_menu(Menu *menu, Dimension *scr_dim)
{
    WinContext wctx;
    Dimension dim;

    wctx.dimension = &dim;
    menu->init_handler(&wctx, scr_dim);

    int16_t input = 0;
    select_t select = 0;

    // Displays the menu window until the RETURN key
    // is pressed signifying a menu button press.
    do
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
            return menu->screen_handler;
        }

        // Updates the selection and displays the menu.
        select = (select + menu->item_count) % menu->item_count;
        menu->display_handler(&wctx, select);

    } while ((input = getch()) != ASCII_LF);

    return menu->return_handlers[select];
}

/**
 * @brief Handles the main menu interface.
 *
 * @details This function displays the main menu window and handles user
 * input for triggering the actions associated with the main menu buttons.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
size_t handle_main_menu(Dimension *scr_dim)
{
    Menu menu = {
        init_main_menu,
        show_main_menu,
        HDL_MAIN_MENU,
        main_menu_option_cnt,
        main_menu_handlers,
    };

    return handle_menu(&menu, scr_dim);
}

/**
 * @brief Handles the pause menu interface.
 *
 * @details This function displays the pause menu window and handles user
 * input for triggering the actions associated with the pause menu buttons.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
size_t handle_pause_menu(Dimension *scr_dim)
{
    Menu menu = {
        init_pause_menu,
        show_pause_menu,
        HDL_PAUSE_MENU,
        pause_menu_option_cnt,
        pause_menu_handlers,
    };

    return handle_menu(&menu, scr_dim);
}

/**
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

/**
 * @brief Handles the end game dialog interface.
 *
 * @details Displays the appropriate end game dialog based
 * on the game result and waits for user input to proceed.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
size_t handle_end_game_dialog(Dimension *scr_dim)
{
    int16_t input;

    if (game.max_val == target)
        show_end_game_dialog(win_dialog_txt, win_dialog_txt_len, scr_dim);

    else
        show_end_game_dialog(lost_dialog_txt, lost_dialog_txt_len, scr_dim);

    // Displays the dialog until the RETURN key is pressed
    // signifying the OK button press.
    while ((input = getch()) != ASCII_LF)
        if (input == KEY_RESIZE)
            return HDL_END_GAME_DIALOG;

    return HDL_MAIN_MENU;
}
