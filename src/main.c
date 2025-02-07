#include <ncurses.h>
#include <stdlib.h>

#include "shared.h"
#include "core.h"
#include "consts.h"

#include "interface/common.h"
#include "interface/core.h"

Screen *setup(void)
{
    Screen *scrs = (Screen *)calloc(screen_count, sizeof(Screen));

    for (size_t i = 0; i < screen_count; ++i)
        scrs[i].dimension = (Dimension *)malloc(sizeof(Dimension));

    init_screen(scrs);
    get_screen_dimension(scrs);

    for (size_t i = 1; i < screen_count; ++i)
        scrs[i].window = init_window();

    return scrs;
}

void clean(Screen *scrs)
{
    for (size_t i = 0; i < screen_count; ++i)
    {
        delwin(scrs[i].window);
        free(scrs[i].dimension);
    }

    free(scrs);
}
