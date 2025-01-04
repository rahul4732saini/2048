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

void display_header_footer(struct Screen *screen)
{
    size_t st_pos = (screen->width - strlen(header)) / 2;
    mvprintw(1, st_pos, "%s", header);

    for (size_t i = 0; i < footers_size; ++i)
    {
        st_pos = (screen->width - strlen(footers[i])) / 2;
        mvprintw(screen->height - footers_size + i - 1, st_pos, "%s", footers[i]);
    }
}
