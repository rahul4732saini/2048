#ifndef _SHARED_H
#define _SHARED_H

#include <stddef.h>
#include <stdint.h>

#include <ncurses.h>

typedef uint16_t cell_t;
typedef uint8_t select_t;

typedef struct
{
    cell_t **board;
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
} WinContext;

typedef struct
{
    void (*init_handler)(WinContext *, Dimension *);
    void (*display_handler)(WinContext *, size_t);
    const size_t screen_handler;
    const size_t item_count;
    const size_t *return_handlers;
} Menu;

#endif
