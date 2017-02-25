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

    Color color_black = { 0, 0, 0, 255 };
    Color color_white = { 255, 255, 255, 255};

    brush.change_color(color_black);
    brush.draw_full();

    brush.change_color(color_white);

    Point p1 = { -5, 5, 0, 0};
    Point p4 = { 5, -5, 0, 0};

    Point p2 = { 5, 5, 0, 0};
    Point p3 = { -5, -5, 0, 0};
 
    
    brush.draw_line(p1, p4);
    brush.draw_line(p2, p3);
    
    screen.update();

    screen.wait_screen(10);
    return 1;
}
