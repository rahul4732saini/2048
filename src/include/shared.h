#ifndef _SHARED_H
#define _SHARED_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

typedef uint16_t cell_t;
typedef uint16_t input_t;
typedef uint8_t select_t;
typedef uint16_t score_t;
typedef int8_t index_t;
typedef uint8_t handler_t;

typedef struct
{
    cell_t **board;
    size_t max_val;
    size_t score;
    bool init;
} Game;

typedef struct
{
    size_t height;
    size_t width;
    size_t start_y;
    size_t start_x;
} Dimension;

typedef struct
{
    WINDOW *window;
    Dimension *dimension;
} WinContext;

#endif
