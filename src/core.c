#include <ncurses.h>
#include <stdint.h>

#include "shared.h"
#include "consts.h"

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
