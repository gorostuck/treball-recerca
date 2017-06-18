/* Este archivo contiene las declaraciones sobre diferentes conceptos geométricos */
#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

struct Point {
  float x;
  float y;
  float z;
  float w;
};

Point vector(Point p1, Point p2);

class Cube {
 public:
  Cube();
  Cube(Point P[8]);
  virtual ~Cube();

  void translate(int axis, float value);
  Point translate(Point point);
  void rotate(int axis, float value);
  void rotate_local(int axis, float value);

  Point center_of_cube();

  Point P[8];
};

#endif /* GEOMETRY_H_INCLUDED */
