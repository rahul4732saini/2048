#include <ncurses.h>
#include <stdlib.h>

#include "core.h"
#include "shared.h"

#include "interface/common.h"
#include "interface/core.h"

Screen *setup(void)
{
    Screen *scrs = (Screen *)calloc(3, sizeof(Screen));

    for (size_t i = 0; i < 3; ++i)
        scrs[i].dimension = (Dimension *)malloc(sizeof(Dimension));

    init_screen(scrs);
    get_screen_dimension(scrs);

    for (size_t i = 1; i < 3; ++i)
        scrs[i].window = init_window();

    return scrs;
}
