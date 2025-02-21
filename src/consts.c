/*
 * @file consts.c
 * @brief Defines constants used throughout the game for assistance.
 */

#include <stdlib.h>

const size_t screen_count = 3;
const size_t target = 2048;

// Define the width and heigh of each tile on the game board.
const size_t cell_width = 8;
const size_t cell_height = 3;

const char *headers[] = {
    "2048 Game",
};

const char *footers[] = {
    "Made by Rahul Saini",
    "Visit https://www.github.com/rahul4732saini/2048 for more info",
};

// Length of the headers and footers array.
const size_t headers_size = 1;
const size_t footers_size = 2;

// Horizontal and vertical margins for the game  window. A additional
// height of 4 is added in the vertical margin to display empty lines
// between the game window and the screen edges.
const size_t win_vertical_margins = headers_size + footers_size + 4;
const size_t win_horizontal_margins = 0;

const char *main_menu_title = "Main Menu";
const char *pause_menu_title = "Pause Menu";

const char *main_menu_items[] = {"Play", "Quit"};
const char *pause_menu_items[] = {
    "Resume",
    "Quit to Main Menu",
    "Quit Game",
};

const size_t main_menu_items_size = 2;
const size_t pause_menu_items_size = 3;

// Widths of the main menu and pause menu window,
// and the width of the dialog box window button.
const size_t main_menu_width = 20;
const size_t pause_menu_width = 25;
const size_t dialog_bt_width = 10;

const char *dialog_bt_txt = "OK";

const char *win_dialog_txt[] = {"You won the game!"};
const char *lost_dialog_txt[] = {"You lost the game!", "Better luck next time..."};

const size_t win_dialog_txt_len = 1;
const size_t lost_dialog_txt_len = 2;
