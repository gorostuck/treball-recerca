#include "screen.h"

#include <stdio.h>

Screen::Screen()
{
    //ctor
}

Screen::~Screen()
{
    //dtor
}

int Screen::start_screen(void)
{
  if (SDL_Init(SDL_INIT_VIDEO)){
    printf("SDL no se ha podido iniciar correctamente: %s\n", SDL_GetError());
    return 1;
  }

  if (SDL_CreateWindowAndRenderer(DEFAULT_MAX_SCREEN_X,DEFAULT_MAX_SCREEN_Y, SDL_WINDOW_RESIZABLE, &window, &renderer)){
    if (window == NULL){
        printf("La ventana no se ha creado con éxito: %s\n", SDL_GetError());
        return 1;
    } if (renderer == NULL) {
        printf("El renderer no se ha creado con éxito: %s\n", SDL_GetError());
    }
  }

  max_x = DEFAULT_MAX_SCREEN_X;
  max_y = DEFAULT_MAX_SCREEN_Y;
  return 0;
}

int Screen::end_screen(void)
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
 
  return 0;
}

void Screen::wait_screen(int time)
{
  SDL_Delay(time);
}

void Screen::draw_screen()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(renderer, 0, 0, max_x, max_y);
  SDL_RenderDrawLine(renderer, max_x, 0, 0, max_y);
  SDL_RenderPresent(renderer);
}

void Screen::update_size()
{
  SDL_GetWindowSize(window, &max_x, &max_y);
}
