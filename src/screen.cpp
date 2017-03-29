/* Este archivo contiene las definiciones sobre diversos
   aspectos de la ventana */
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

void Screen::change_color(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Screen::draw_full()
{
  SDL_RenderClear(renderer);
}

void Screen::draw_point(int x, int y)
{
  SDL_RenderDrawPoint(renderer, x, y);
}

void Screen::draw_line(int begin_x, int begin_y, int end_x, int end_y)
{
  SDL_RenderDrawLine(renderer, begin_x, begin_y, end_x, end_y);
}

void Screen::draw_my_line(int begin_x, int begin_y, int end_x, int end_y)
{
  float v_1 = end_x - begin_x;
  float v_2 = end_y - begin_y;

  float t = 1/(abs(v_1) + abs(v_2));
  v_1 *= t;
  v_2 *= t;

  float point_x = begin_x;
  float point_y = begin_y;

  for (;(int)abs(point_x-end_x)>1 && (int)abs(point_y-end_y)>1;point_x +=v_1, point_y +=v_2)
    {
      SDL_RenderDrawPoint(renderer, (int)point_x, (int)point_y);
    }
}

void Screen::update()
{
  SDL_RenderPresent(renderer);
}
