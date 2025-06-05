/**
 * @file main.c
 * @brief Entry point for the TUI-based 2048 game.
 *
 * @details This file comprises the main function and the core setup and cleanup
 *          routines for the text-based user interface (TUI) using ncurses. It
 *          initializes the TUI environment, manages the game loop, and ensures
 *          proper resource cleanup before exiting.
 *
 * @author rahul4732saini
 */

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "shared.h"
#include "core.h"
#include "consts.h"

#include "interface/shared.h"
#include "interface/core.h"

// Stores references to the screen handler functions.
const size_t (*handlers[])(Dimension *) = {

    // The first index is reserved and signifies the EXIT handler.
    (size_t (*)(Dimension *))NULL,

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
int main()
{
    srand(time(NULL));

    // Sets up the TUI environments and the required color pairs.
    Screen *scrs = setup();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    // Handles the game execution loop while the associated function
    // does not return a non-zero integer signifying a closure.
    while (handle_game(scrs))
        ;

    // Cleans the TUI environment and closes the standard TUI screen.
    clean(scrs);
    endwin();

    return EXIT_SUCCESS;
}
