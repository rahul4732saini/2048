#ifndef _SHARED_H
#define _SHARED_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

typedef uint16_t cell_t;
typedef uint16_t input_t;
typedef uint8_t select_t;
typedef uint32_t score_t;
typedef int8_t index_t;
typedef uint16_t pos_t;
typedef uint16_t len_t;
typedef uint8_t handler_t;

typedef struct
{
    cell_t **board;
    cell_t max_val;
    score_t score;
    bool init;
} Game;

typedef struct
{
    len_t height;
    len_t width;
    pos_t start_y;
    pos_t start_x;
} Dimension;

typedef struct
{
    WINDOW *window;
    Dimension *dimension;
} WinContext;

#endif
