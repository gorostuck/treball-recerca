#include "screen.h"

#include <SDL2/SDL.h>

int max_x, max_y;
SDL_Window *window;
SDL_Renderer *renderer;

int screen_start(void)
{
  if (SDL_Init(SDL_INIT_VIDEO)){
    printf("SDL no se ha podido iniciar correctamente: %s\n", SDL_GetError());
    return 1;
  }

  if (SDL_CreateWindowAndRenderer(DEFAULT_MAX_SCREEN_X,DEFAULT_MAX_SCREEN_Y,
				  SDL_WINDOW_RESIZABLE, &window, &renderer)){
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

int screen_end(void)
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
 
  return 0;
}

void screen_wait(int time)
{
  SDL_Delay(time);
}


void screen_update_size()
{
  SDL_GetWindowSize(window, &max_x, &max_y);
}

void screen_change_color(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void screen_draw_full()
{
  SDL_RenderClear(renderer);
}

void screen_draw_point(int x, int y)
{
  SDL_RenderDrawPoint(renderer, x, y);
}

void screen_draw_line(int begin_x, int begin_y, int end_x, int end_y)
{
  SDL_RenderDrawLine(renderer, begin_x, begin_y, end_x, end_y);
}

void screen_update()
{
  SDL_RenderPresent(renderer);
}
