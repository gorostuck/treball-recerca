/* Este archivo contiene las definiciones sobre la lógica
de la simulación y la gestión de eventos */
#include "logic.h"

#include "screen.h"

SDL_Event event;

int logic_start(void)
{
    if (start_screen())
        return 1;

    while (logic_loop());
    end_screen();

    return 0;
}

int logic_loop(void)
{
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        return 0;
    draw_screen();
    wait_screen(100);
    return 1;
}
