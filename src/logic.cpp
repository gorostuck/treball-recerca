/* Este archivo contiene las definiciones sobre la lógica
de la simulación y la gestión de eventos */
#include "logic.h"

#include "screen.h"

SDL_Event event;
Screen screen;

int logic_start(void)
{
    if (screen.start_screen())
        return 1;

    while (logic_loop());
    screen.end_screen();

    return 0;
}

int logic_loop(void)
{
    SDL_PollEvent(&event);
    if (event.type == SDL_WINDOWEVENT){
      switch (event.window.event){
      case SDL_WINDOWEVENT_SIZE_CHANGED:
	screen.update_size();
	break;
      }
    }
    if (event.type == SDL_QUIT)
      return 0;
    screen.draw_screen();
    screen.wait_screen(10);
    return 1;
}
