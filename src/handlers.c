/**
 * @file handlers.c
 * @brief Defines screen handler functions for managing in-game interfaces.
 *
 * @details This module defines screen handler functions for managing
 * in-game TUI interfaces, including user input management and integration
 * of the logic associated with them.
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
 * @brief Handles the main menu interface.
 *
 * @details Displays the main menu window and handles user input for
 * triggering the actions associated with the main menu buttons.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
handler_t handle_main_menu(Dimension *scr_dim)
{
    WinContext wctx;
    Dimension dim;

    wctx.dimension = &dim;
    init_main_menu(&wctx, scr_dim);

    input_t input = 0;
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
            return HDL_MAIN_MENU;
        }

        // Updates the selection and displays the menu.
        select = (select + main_menu_option_cnt) % main_menu_option_cnt;
        show_main_menu(&wctx, select);

    } while ((input = getch()) != ASCII_LF);

    return main_menu_handlers[select];
}

/**
 * @brief Handles the pause menu interface.
 *
 * @details Displays the pause menu window and handles user input for
 * triggering the actions associated with the pause menu buttons.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
handler_t handle_pause_menu(Dimension *scr_dim)
{
    WinContext wctx;
    Dimension dim;

    wctx.dimension = &dim;
    init_pause_menu(&wctx, scr_dim);

    input_t input = 0;
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
            return HDL_PAUSE_MENU;

        // Pressing the ESC key redirects back to the game window.
        case ASCII_ESC:
            return HDL_GAME_WIN;
        }

        // Updates the selection and displays the menu.
        select = (select + pause_menu_option_cnt) % pause_menu_option_cnt;
        show_pause_menu(&wctx, select);

    } while ((input = getch()) != ASCII_LF);

    // The game session is terminated if the player selects to leave.
    if (pause_menu_handlers[select] != HDL_GAME_WIN)
        game.init = false;

    return pause_menu_handlers[select];
}

/**
 * @brief Handles the game board interface.
 *
 * @details Displays the game board window and handles user input, and
 * the complete game mechanics including tile operations, random value
 * placement, and game over condition check at each move during the
 * gameplay.
 *
 * @param scr_dim Pointer to the Dimension struct comprising the
 * screen dimensions.
 *
 * @return A non-negative integer indicating the screen
 * handler to be called next in the game execution loop.
 */
handler_t handle_game_board(Dimension *scr_dim)
{
    WinContext wctx;
    Dimension dim;

    wctx.dimension = &dim;
    init_game_win(&wctx, scr_dim);

    if (!game.init)
        setup_game(&game);

    // The 'iskey' stores whether the input is the up or left
    // arrow key, to determine the direction of operation.

    input_t input = 0;
    bool iskey, isempty, operated;

    // Displays the game board and handles the game mechanics
    // until the ESC key is pressed to open the pause menu.
    do
    {
        operated = false, isempty = true;
        iskey = input == KEY_UP || input == KEY_LEFT;

        switch (input)
        {
        case KEY_UP:
        case KEY_DOWN:
            operated |= add_vertical(&game, iskey);
            operated |= move_vertical(&game, iskey);
            break;

        case KEY_LEFT:
        case KEY_RIGHT:
            operated |= add_horizontal(&game, iskey);
            operated |= move_horizontal(&game, iskey);
            break;

        case KEY_RESIZE:
            return HDL_GAME_WIN;
        }

        // Random value is only placed if any operations are performed.
        if (operated)
            isempty = place_random(&game);

        show_board(&wctx, &game);

        // Terminates the game if either of the termintation conditions are met.
        if (is_game_over(&game, isempty) || game.max_val == TARGET)
        {
            game.init = false;
            return HDL_END_GAME_DIALOG;
        }

    } while ((input = getch()) != ASCII_ESC);

    return HDL_PAUSE_MENU;
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
handler_t handle_end_game_dialog(Dimension *scr_dim)
{
    input_t input;

    if (game.max_val == TARGET)
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
