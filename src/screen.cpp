#include "screen.h"
#include <stdio.h>

cScreen::cScreen()
{
    //ctor
}

cScreen::~cScreen()
{
    //dtor
}

int cScreen::start_screen(void)
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

int cScreen::end_screen(void)
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();

  return 0;
}

void cScreen::wait_screen(int time)
{
  SDL_Delay(time);
}

void cScreen::draw_screen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, MAX_SCREEN_X, MAX_SCREEN_Y);
    SDL_RenderDrawLine(renderer, MAX_SCREEN_X, 0, 0, MAX_SCREEN_Y);
    SDL_RenderPresent(renderer);
}
