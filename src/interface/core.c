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
    size_t st_pos;

    for (size_t i = 0; i < headers_size; ++i)
    {
        st_pos = (screen->width - strlen(headers[i])) / 2;
        mvprintw(1 + i, st_pos, "%s", headers[i]);
    }

    for (size_t i = 0; i < footers_size; ++i)
    {
        st_pos = (screen->width - strlen(footers[i])) / 2;
        mvprintw(screen->height - footers_size + i - 1, st_pos, "%s", footers[i]);
    }
}
