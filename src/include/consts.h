#ifndef _CONSTS_H
#define _CONSTS_H

#include <stdlib.h>

#define BOARD_SIZE 4
#define TARGET 2048

#define MIN_HEIGHT 25
#define MIN_WIDTH 80

// Width and height of each cell in the game board.
#define CELL_HEIGHT 3
#define CELL_WIDTH 8

#define BOARD_HEIGHT (CELL_HEIGHT + 1) * BOARD_SIZE + 1
#define BOARD_WIDTH (CELL_WIDTH + 1) * BOARD_SIZE + 1

// Index values used to identify the handler functions
// associated with the corresponding in-game screens.
#define HDL_EXIT 0
#define HDL_MAIN_MENU 1
#define HDL_PAUSE_MENU 2
#define HDL_GAME_WIN 3
#define HDL_END_GAME_DIALOG 4

#define COLOR_SELECT 1

#define ASCII_ESC 27
#define ASCII_LF 10

extern const char *scr_dim_warning;

extern const char *headers[];
extern const char *footers[];

extern const size_t headers_len;
extern const size_t footers_len;

extern const char *main_menu_title;
extern const char *pause_menu_title;

extern const char *main_menu_options[];
extern const size_t main_menu_option_cnt;
extern const size_t main_menu_width;

extern const char *pause_menu_options[];
extern const size_t pause_menu_option_cnt;
extern const size_t pause_menu_width;

extern const char *dialog_bt_txt;
extern const size_t dialog_bt_width;

extern const char *win_dialog_txt[];
extern const size_t win_dialog_txt_len;

extern const char *lost_dialog_txt[];
extern const size_t lost_dialog_txt_len;

extern const size_t main_menu_handlers[];
extern const size_t pause_menu_handlers[];

#endif
