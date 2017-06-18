/* Este archivo contiene las declaraciones sobre la
   clase usada para pintar geometría en la pantalla */
#ifndef BRUSH_H_INCLUDED
#define BRUSH_H_INCLUDED

#define DEFAULT_MAX_X 10
#define DEFAULT_MIN_X -10
#define DEFAULT_MAX_Y 10
#define DEFAULT_MIN_Y -10


struct Color {
  int r;
  int g;
  int b;
  int a;
};

#include "screen.h"
#include "geometry.h"


class Brush
{
 public:
  Brush();
  virtual ~Brush();
  void start_brush(Screen *_screen);

  void draw_point(Point point);
  void draw_full();
  void draw_line(Point start_point, Point end_point);
  void draw_line_alt(Point start_point, Point end_point, int k);

  void change_color(Color color);

  Point real_from_screen(Point point);
  Point screen_from_real(Point point);

  int max_x;
  int min_x;
  int max_y;
  int min_y;

 private:
  Screen *screen;

  float x_real_from_x_screen(int x_screen);
  float y_real_from_y_screen(int y_screen);

  int x_screen_from_x_real(float x_real);
  int y_screen_from_y_real(float y_real);
};

#endif // BRUSH_H_INCLUDED



