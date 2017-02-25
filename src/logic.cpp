/* Este archivo contiene las definiciones sobre la lógica
de la simulación y la gestión de eventos */
#include "logic.h"

#include <stdio.h>

#include "screen.h"
#include "brush.h"

SDL_Event event;
Screen screen;
Brush brush;

int logic_start(void)
{
    if (screen.start_screen())
        return 1;
    brush.start_brush(&screen);

    printf("\nx| Pantalla: %d -> Real: %d", 512, brush.x_real_from_x_screen(512));
    printf("\ny| Pantalla: %d -> Real: %d", 512, brush.y_real_from_y_screen(512));
    printf("\nx| Real: %d -> Pantalla: %d", 10, brush.x_screen_from_x_real(10));
    printf("\ny| Real: %d -> Pantalla: %d\n",10, brush.y_screen_from_y_real(10));

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

    // Draw time:
    screen.change_color(0, 0, 0, 255);
    screen.draw_full();
    screen.change_color(255, 255, 255, 255);
    screen.draw_line(0, 0, screen.max_x, screen.max_y);
    screen.draw_line(screen.max_x, 0, 0, screen.max_y);

    screen.update();

    screen.wait_screen(10);
    return 1;
}
