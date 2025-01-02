#ifndef _SHARED_H
#define _SHARED_H

#include <stddef.h>
#include <stdint.h>

typedef uint16_t cell_t;

struct GameStatus
{
    size_t max_val;
    size_t score;
};

#endif
