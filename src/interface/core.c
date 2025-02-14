#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

#include "interface/shared.h"

void init_screen(Screen *scr)
{
    initscr();

    cbreak();
    noecho();
    start_color();

    curs_set(0);
    keypad(stdscr, TRUE);

    scr->window = stdscr;
}

void get_screen_dimension(Screen *scr)
{
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

void show_dialog(Screen *scr, const char *mesg[], size_t mesg_len, int select_color)
{
    Dimension *dim = scr->dimension;
    WINDOW *win = scr->window;

    size_t cur_x, cur_y = (dim->height - mesg_len - 2) / 2;

    for (size_t i = 0; i < mesg_len; ++i)
    {
        cur_x = (dim->width - strlen(mesg[i])) / 2;

        wmove(win, cur_y++, cur_x);
        wprintw(win, "%s", mesg[i]);
    }

    cur_x = (dim->width - dialog_bt_width) / 2;
    size_t left_cutoff = (dialog_bt_width - strlen(dialog_bt_txt)) / 2;

    wmove(win, ++cur_y, cur_x);
    wattron(win, COLOR_PAIR(select_color));

    wprintw(win, "%*s", left_cutoff, "");
    wprintw(win, "%s", dialog_bt_txt);
    wprintw(win, "%*s", dialog_bt_width - left_cutoff - strlen(dialog_bt_txt), "");

    wattroff(win, COLOR_PAIR(select_color));
    wrefresh(win);
}

void refresh_game_win(Screen *game_scr, Screen *core_scr, const char *title)
{
    clear();
    refresh();

    get_screen_dimension(core_scr);
    place_game_win(game_scr, core_scr);

    show_game_win(game_scr);

    show_header_footer(core_scr);
    show_window_title(game_scr, title);
}