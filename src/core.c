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
 * @return Returns an integer code to indicate the pressed button signifying
 *         the action which needs to be triggered. The codes along with
 *         their actions are as follows:
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
 * @return Returns an integer code to indicate the pressed button signifying
 *         the action which needs to be triggered. The codes along with
 *         their actions are as follows:
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

static int8_t handle_game_board(Screen *scrs, Game *game)
{
    int16_t input, operations;
    bool iskey, isempty;

    static char score[20];

    place_board(scrs + 2, scrs + 1, game->bsize);
    show_board(scrs + 2, game);

    sprintf(score, "Score: %zu", game->score);
    show_window_title(scrs + 1, score);

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

        sprintf(score, "Score: %zu", game->score);

        show_window_title(scrs + 1, score);
        show_board(scrs + 2, game);
    }

    return 1;
}

static int8_t handle_dialog(Screen *game_win, const char *mesg[], size_t mesg_len, int select_color)
{
    show_dialog(game_win, mesg, mesg_len, select_color);

    int16_t input;

    while ((input = getch()) != 10)
        if (input == KEY_RESIZE)
            return -1;

    return 0;
}

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

int8_t handle_game(Screen *scrs)
{
    int8_t status;

    do
        refresh_game_win(scrs + 1, scrs, main_menu_title);
    while ((status = handle_main_menu(scrs)) < 0);

    if (status == 1)
        return 0;

    Game game = setup_game();
    refresh_game_win(scrs + 1, scrs, "");

    while ((status = handle_game_board(scrs, &game)))
    {
        if (status < 0)
        {
            refresh_game_win(scrs + 1, scrs, "");
            continue;
        }

        do
            refresh_game_win(scrs + 1, scrs, pause_menu_title);
        while ((status = handle_pause_menu(scrs)) < 0);

        if (status == 1)
            return 1;

        else if (status == 2)
            return 0;

        refresh_game_win(scrs + 1, scrs, "");
    }

    refresh_game_win(scrs + 1, scrs, "");

    if (game.max_val == target)
        handle_dialog(scrs + 1, win_dialog_txt, win_dialog_txt_len, 1);

    else
        handle_dialog(scrs + 1, lost_dialog_txt, lost_dialog_txt_len, 1);

    return 1;
}