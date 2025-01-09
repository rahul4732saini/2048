#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

void init_screen(void)
{
    initscr();

    cbreak();
    noecho();

    keypad(stdscr, TRUE);
}

void init_game_win(WINDOW **window, struct Screen *screen)
{
    size_t height = screen->height - win_vertical_margins;
    size_t width = screen->width - win_horizontal_margins;

    *window = newwin(
        height,
        width,
        win_vertical_margins / 2,
        win_horizontal_margins / 2);

    refresh();

    keypad(*window, TRUE);

    box(*window, 0, 0);
    wrefresh(*window);
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
