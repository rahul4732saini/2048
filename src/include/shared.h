#ifndef _SHARED_H
#define _SHARED_H

#include <stddef.h>
#include <stdint.h>

#include <ncurses.h>

typedef uint16_t cell_t;

typedef struct
{
    cell_t **board;
    size_t bsize;
    size_t max_val;
    size_t score;
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
} Screen;

#endif
