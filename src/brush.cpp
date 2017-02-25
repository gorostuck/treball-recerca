/* Este archivo contiene las definiciones sobre
   la clase usada para pintar geometría en la pantalla */
#include "brush.h"

Brush::Brush()
{
}

Brush::~Brush()
{
}

void Brush::start_brush(Screen *_screen)
{
  max_x = DEFAULT_MAX_X;
  min_x = DEFAULT_MIN_Y;
  max_y = DEFAULT_MAX_Y;
  min_y = DEFAULT_MIN_Y;
  screen = _screen;
}

Point Brush::real_from_screen(Point point)
{
  Point new_point = { 0, 0, 0, 0};
  return new_point;
}

Point Brush::screen_from_real(Point point)
{
  Point new_point = { 0, 0, 0, 0};
  return new_point;
}

int Brush::x_real_from_x_screen(int x_screen)
{
  return ((x_screen / screen->max_x) * (max_x - min_x)) + min_x;
}

int Brush::x_screen_from_x_real(int x_real)
{
  return ((x_real - min_x) / (max_x - min_x)) * screen->max_x;
}

int Brush::y_real_from_y_screen(int y_screen)
{
  return (1 - (y_screen / screen->max_y)) * (max_y - min_y) + min_y;
}

int Brush::y_screen_from_y_real(int y_real)
{
  return (1 - ((y_real - min_y) / (max_y - min_y))) * screen->max_y;
}
