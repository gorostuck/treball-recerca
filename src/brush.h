/* Este archivo contiene las declaraciones sobre la
   clase usada para pintar geometría en la pantalla */
#ifndef BRUSH_H_INCLUDED
#define BRUSH_H_INCLUDED

#define DEFAULT_MAX_X 10
#define DEFAULT_MIN_X -10
#define DEFAULT_MAX_Y 10
#define DEFAULT_MIN_Y -10

struct Point {
  int x;
  int y;
  int z;
  int w;
};

#include "screen.h"

class Brush
{
 public:
  Brush();
  virtual ~Brush();
  void start_brush(Screen *_screen);
  Point real_from_screen(Point point);
  Point screen_from_real(Point point);


// Provisional 
  int x_real_from_x_screen(int x_screen);
  int x_screen_from_x_real(int x_real);
  int y_real_from_y_screen(int y_screen);
  int y_screen_from_y_real(int y_real);

 protected:
 private:
  int max_x;
  int min_x;
  int max_y;
  int min_y;

  Screen *screen;


};

#endif // BRUSH_H_INCLUDED
