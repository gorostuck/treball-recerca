/* Este archivo contiene las declaraciones sobre la l�gica
de la simulaci�n y la gesti�n de eventos */
#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

struct Point {
  float x;
  float y;
  float z;
  float w;
};

struct Cube {
  Point P[8];
};

int logic_start(void);
int logic_loop(void);


void fill_cube(Cube *cube, Point point[8]);
void translate_cube(Cube *cube, int axis, int value);
void rotate_cube(Cube *cube, int axis, int value);
void render_cube(Cube *cube, Point O, float t, float k);

#endif // LOGIC_H_INCLUDED
