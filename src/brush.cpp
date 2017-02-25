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

void Brush::draw_point(Point real_point)
{
  Point screen_point = screen_from_real(real_point);
  screen->draw_point(screen_point.x, screen_point.y);
}

void Brush::draw_line(Point start_real_point, Point end_real_point)
{
  Point start_screen_point = screen_from_real(start_real_point);
  Point end_screen_point   = screen_from_real(end_real_point);
  screen->draw_line(start_screen_point.x, start_screen_point.y,
		    end_screen_point.x, end_screen_point.y);
}

void Brush::draw_full()
{
  screen->draw_full();
}
void Brush::change_color(Color color)
{
  screen->change_color(color.r, color.g, color.b, color.a);
}

Point Brush::real_from_screen(Point point)
{
  Point new_point = { x_real_from_x_screen(point.x),
		      y_real_from_y_screen(point.y),
		      point.z, point.w };
  return new_point;
}

Point Brush::screen_from_real(Point point)
{
  Point new_point = { x_screen_from_x_real(point.x),
		      y_screen_from_y_real(point.y),
		      point.z, point.w };
  return new_point;
}

int Brush::x_real_from_x_screen(int x_screen)
{
  return ((float) (x_screen / screen->max_x) * (max_x - min_x)) + min_x;
}

int Brush::x_screen_from_x_real(int x_real)
{
  return ((float) (x_real - min_x) / (max_x - min_x)) * screen->max_x;
}

int Brush::y_real_from_y_screen(int y_screen)
{
  return (1 - (float) (y_screen / screen->max_y)) * (max_y - min_y) + min_y;
}

int Brush::y_screen_from_y_real(int y_real)
{
  return (1 - (float) (y_real - min_y) / (max_y - min_y)) * screen->max_y;
}
























