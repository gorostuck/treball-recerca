/* Este archivo contiene las declaraciones sobre la lógica
de la simulación y la gestión de eventos */
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
} observer = { 0., 0., 0., 0. };

struct Cube {
  Point P[8];
} *main_cube, *reset_cube;

float k;

int logic_start(void);
int logic_loop(void);


void fill_cube(Cube *cube, Point point[8]);
void translate_cube(Cube *cube, int axis, float value);
void rotate_cube(Cube *cube, int axis, float value);
void render_cube(Cube *cube);

#endif // LOGIC_H_INCLUDED
