#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

#include "interface/common.h"

void init_screen(Screen *scr)
{
    initscr();

    cbreak();
    noecho();
    start_color();

    curs_set(0);
    keypad(stdscr, TRUE);

    scr->window = stdscr;
    Dimension *dim = scr->dimension;

    dim->start_x = dim->start_y = 0;
    getmaxyx(stdscr, dim->height, dim->width);
}

void place_game_win(Screen *scr, Screen *parent)
{
    Dimension *dim_scr = scr->dimension, *dim_parent = parent->dimension;

    dim_scr->width = dim_parent->width - win_horizontal_margins;
    dim_scr->height = dim_parent->height - win_vertical_margins;

    dim_scr->start_x = win_horizontal_margins / 2;
    dim_scr->start_y = win_vertical_margins / 2;

    place_window(scr);
}

void show_header_footer(Screen *scr)
{
    Dimension *dim = scr->dimension;
    size_t st_pos;

    for (size_t i = 0; i < headers_size; ++i)
    {
        st_pos = (dim->width - strlen(headers[i])) / 2;
        mvprintw(1 + i, st_pos, "%s", headers[i]);
    }

    for (size_t i = 0; i < footers_size; ++i)
    {
        st_pos = (dim->width - strlen(footers[i])) / 2;
        mvprintw(dim->height - footers_size + i - 1, st_pos, "%s", footers[i]);
    }

    wrefresh(scr->window);
}

void show_game_win(Screen *scr)
{
    box(scr->window, 0, 0);
    wrefresh(scr->window);
}

void show_window_title(Screen *scr, const char *title)
{
    size_t start_x = (scr->dimension->width - strlen(title)) / 2;

    mvwprintw(scr->window, 2, start_x, "%s", title);
    wrefresh(scr->window);
}
