/*
 * @file main.c
 * @brief Entry point for the TUI-based 2048 game.
 *
 * This file contains the main function and the core setup and cleanup
 * routines for the text-based user interface (TUI) using ncurses. It
 * initializes the TUI environment, manages the game loop, and ensures
 * proper resource cleanup before exiting.
 *
 * @author rahul4732saini
 */

#include <ncurses.h>
#include <stdlib.h>

#include "shared.h"
#include "core.h"
#include "consts.h"

#include "interface/shared.h"
#include "interface/core.h"

/*
 * Initializes the TUI environment for the game.
 *
 * Sets up the Screen and Dimensions structures for encapsulating the TUI
 * windows and their associated dimensions. It also initializes the standard
 * TUI screen and other game windows.
 *
 * @return A pointer to the first Screen in the dynamically allocated screens
 *         array, representing the TUI windows.
 */
Screen *setup(void)
{
    Screen *scrs = (Screen *)calloc(screen_count, sizeof(Screen));

    for (size_t i = 0; i < screen_count; ++i)
        scrs[i].dimension = (Dimension *)malloc(sizeof(Dimension));

    init_screen(scrs);
    get_screen_dimension(scrs);

    for (size_t i = 1; i < screen_count; ++i)
        scrs[i].window = init_window();

    return scrs;
}

/*
 * Cleans the TUI environment before closure.
 *
 * Frees the dynamically allocated memory for the TUI windows, their associated
 * Dimension structs and the screens array comprising the Screen structs.
 */
void clean(Screen *scrs)
{
    for (size_t i = 0; i < screen_count; ++i)
    {
        delwin(scrs[i].window);
        free(scrs[i].dimension);
    }

    free(scrs);
}

/*
 * Main function for program execution.
 */
int main()
{
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
