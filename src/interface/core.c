#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

void initialize_screen(void)
{
    initscr();

    cbreak();
    noecho();
}
