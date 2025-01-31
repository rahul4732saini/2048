#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>

#include "logic.h"
#include "shared.h"
#include "consts.h"

#include "interface/board.h"
#include "interface/menu.h"

int8_t handle_main_menu(Screen *scrs)
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

int8_t handle_pause_menu(Screen *scrs)
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

int8_t handle_game_board(Screen *scrs, Game *game)
{
    int16_t input, operations;
    bool iskey, isempty;

    place_board(scrs + 2, scrs, game->bsize);
    show_board(scrs + 2, game);

    while ((input = getch()) != KEY_EXIT)
    {
        operations = 0;
        isempty = true;

        switch (input)
        {
        case KEY_UP:
        case KEY_DOWN:
            iskey = input == KEY_UP;

            operations += add_vertical(game, iskey);
            operations += move_vertical(game, iskey);
            break;

        case KEY_LEFT:
        case KEY_RIGHT:
            iskey = input == KEY_LEFT;

            operations += add_horizontal(game, iskey);
            operations += move_horizontal(game, iskey);
            break;

        case KEY_RESIZE:
            return -1;
        }

        if (operations)
            isempty = place_random(game);

        if (game_over(game, isempty) || game->max_val == 2048)
            return 0;

        show_board(scrs + 2, game);
    }

    return 1;
}
