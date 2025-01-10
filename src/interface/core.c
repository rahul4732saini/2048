#include <ncurses.h>
#include <string.h>

#include "consts.h"
#include "shared.h"

void init_screen(void)
{
    initscr();

    cbreak();
    noecho();
    start_color();

    curs_set(0);
    keypad(stdscr, TRUE);
}

void init_game_win(WINDOW **window, Screen *screen)
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
}

void show_header_footer(Screen *screen)
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

void show_game_win(WINDOW *window)
{
    box(window, 0, 0);
    wrefresh(window);
}

void show_window_title(WINDOW *window, Screen *screen, const char *title)
{
    size_t start_x = (screen->width - strlen(main_menu_title)) / 2;

    mvwprintw(window, 2, start_x, "%s", main_menu_title);
    wrefresh(window);
}
