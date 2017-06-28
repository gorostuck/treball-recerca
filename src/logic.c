/* Este archivo contiene las definiciones sobre la lógica de la simulación y la gestión de eventos */
#include "logic.h"
#include "screen.h"

#include <SDL2/SDL.h>

SDL_Event event;

int logic_start()
{
  if (screen_start())
    return 1;
  while (logic_loop());
  screen_end();
  return 0;
  
}

int logic_loop()
{
  SDL_PollEvent(&event);
      if (event.type == SDL_WINDOWEVENT){
      switch (event.window.event){
      case SDL_WINDOWEVENT_SIZE_CHANGED:
	screen_update_size();
	break;
      }
    }
    if (event.type == SDL_QUIT)
      return 0;
    return 1;
}
