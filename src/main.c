/**
 * @file main.c
 * @brief Entry point for the TUI-based 2048 game.
 *
 * @details This file comprises the main function and the core setup and
 * cleanup routines for the TUI environment. It defines the mechanism to
 * handle the game execution loop, and ensure proper setup and cleanup of
 * resources at expected intervals.
 *
 * @author rahul4732saini
 */

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "shared.h"
#include "handlers.h"
#include "consts.h"
#include "logic.h"

#include "interface/shared.h"
#include "interface/core.h"

// Stores references to the screen handler functions.
const handler_t (*handlers[])(Dimension *) = {

    // The first index is reserved and signifies the EXIT handler.
    (handler_t (*)(Dimension *))NULL,

    handle_main_menu,
    handle_pause_menu,
    handle_game_board,
    handle_end_game_dialog,
};

/**
 * @brief Sets up the TUI environment and game-related data structures.
 *
 * @details Sets up TUI environment with ncurses, seeds the random number
 * generator, and sets up the Game struct for handling game-related data.
 */
void setup(void)
{
    srand(time(NULL));

    // Sets up the TUI environment and the required color pairs.
    init_screen();
    init_pair(COLOR_SELECT, COLOR_BLACK, COLOR_WHITE);

    game = (Game){
        .board = create_board(),
        .init = FALSE,
        .score = 0,
        .max_val = 0,
    };
}

/**
 * @brief Cleans the game resources and exits and TUI environment.
 */
void clean(void)
{
    free_board(game.board);
    endwin();
}

/**
 * @brief Main function for program execution.
 */
int main(void)
{
    setup();

    Dimension scr_dim;

    // Stores the index of the current screen handler.
    size_t cur = HDL_MAIN_MENU;

    // Handles the game execution loop until any screen
    // handler return a zero signifying a closure.
    do
    {
        clear();
        scr_dim = (Dimension){getmaxy(stdscr), getmaxx(stdscr)};

        // Displays a warning while the screen dimensions are unsupported.
        if (scr_dim.height < MIN_HEIGHT || scr_dim.width < MIN_WIDTH)
        {
            mvprintw(0, 0, "%s", scr_dim_warning);
            refresh();

            while (getch() != KEY_RESIZE)
                ;

            continue;
        }

        cur = handlers[cur](&scr_dim);

    } while (cur);

    clean();

    return EXIT_SUCCESS;
}
