#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>

#include "logic.h"
#include "shared.h"
#include "consts.h"

#include "interface/core.h"
#include "interface/board.h"
#include "interface/menu.h"

static int8_t handle_main_menu(Screen *scrs)
{
    int16_t input = 0;
    int8_t select = 0;

    place_main_menu(scrs + 2, scrs + 1);
    show_main_menu(scrs + 2, select, 1);

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

static int8_t handle_pause_menu(Screen *scrs)
{
    int16_t input = 0;
    int8_t select = 0;

    place_pause_menu(scrs + 2, scrs + 1);
    show_pause_menu(scrs + 2, select, 1);

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

    sprintf(score, "Score: %d", game->score);
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

        sprintf(score, "Score: %d", game->score);

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
