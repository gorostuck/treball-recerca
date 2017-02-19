/* Este archivo contiene las definiciones sobre diversos
   aspectos de la ventana y la gestion de eventos */
#include "screen.h"

SDL_Window *window;
SDL_Renderer *renderer;

int start_screen(void)
{
  if (SDL_Init(SDL_INIT_VIDEO)){
    printf("SDL no se ha podido iniciar correctamente: %s\n", SDL_GetError());
    return 1;
  }

  if (SDL_CreateWindowAndRenderer(MAX_SCREEN_X,MAX_SCREEN_Y, 0, &window, &renderer)){
    if (window == NULL){
        printf("La ventana no se ha creado con éxito: %s\n", SDL_GetError());
        return 1;
    } if (renderer == NULL) {
        printf("El renderer no se ha creado con éxito: %s\n", SDL_GetError());
    }
  }
  return 0;
}

int end_screen(void)
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();

  return 0;
}

void wait_screen(int time)
{
  SDL_Delay(time);
}

void draw_screen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, MAX_SCREEN_X, MAX_SCREEN_Y);
    SDL_RenderDrawLine(renderer, MAX_SCREEN_X, 0, 0, MAX_SCREEN_Y);
    SDL_RenderPresent(renderer);
}
