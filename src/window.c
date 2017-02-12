/* Este archivo contiene las definiciones sobre diversos
   aspectos de la ventana y la gestion de eventos */
#include "window.h"

int start_screen()
{
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Test",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            512,
                            512,
                            SDL_WINDOW_OPENGL);

  if (window == NULL){
    printf("La ventana no se ha creado con exito: %s\n", SDL_GetError());
    return 1;
  }

  return 0;
}

int end_screen()
{
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}

void wait_screen(int time)
{
  SDL_Delay(time);
}
