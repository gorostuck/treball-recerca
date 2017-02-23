/* Este archivo contiene las definiciones sobre la lógica
de la simulación y la gestión de eventos */
#include "logic.h"

#include "screen.h"

SDL_Event event;

cScreen scr;
int logic_start(void)
{
    if (scr.start_screen())
        return 1;

    while (logic_loop());
    scr.end_screen();

    return 0;
}

int logic_loop(void)
{
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        return 0;
    scr.draw_screen();
    scr.wait_screen(100);
    return 1;
}
