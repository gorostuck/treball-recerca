/* Este archivo contiene las definiciones sobre diferentes conceptos geométricos */
#include "geometry.h"
#include "math.h"

Cube::Cube()
{
}

Cube::Cube(Point P[8])
{
  for (int i = 0; i < 8; ++i){
    this->P[i] = P[i];
  }
}

Cube::~Cube()
{
}

void Cube::translate(int axis, float value)
{
  for (int i = 0; i < 8; ++i){
    switch (axis){
    case AXIS_X:
      P[i].x += value;
      break;
    case AXIS_Y:
      P[i].y += value;
      break;
    case AXIS_Z:
      P[i].z += value;
      break;
    }
  }
}

Point Cube::translate(Point point)
{
  Point t;
  if (point.w == 1) t = point;
  else t = vector(center_of_cube(), point);
  return t;
}

void Cube::rotate_local(int axis, float value)
{
  Point origin = { 0., 0., 0., 0. };
  Point t = translate(origin);
  this->rotate(axis, value);
  for (int i = 0; i < 8; ++i)
    {
      P[i].x -= t.x;
      P[i].y -= t.y;
      P[i].z -= t.z;
    }
}

void Cube::rotate(int axis, float value)
{
    float tmp;
  switch (axis)
    {
    case AXIS_Z:
      for (int i = 0; i < 8; ++i)
	{
	  tmp = P[i].x;
	  P[i].x = cos(value)*P[i].x+sin(value)*P[i].y;
	  P[i].y = -sin(value)*tmp+cos(value)*P[i].y;
	}
      break;
    case AXIS_Y:
       for(int i = 0; i < 8; ++i)
	 {
	   tmp = P[i].x;
	   P[i].x = cos(value)*P[i].x-sin(value)*P[i].z;
	   P[i].z = sin(value)*tmp+cos(value)*P[i].z;
	 }
       break;
    case AXIS_X:
       for(int i = 0; i < 8; ++i)
	 {
	   tmp = P[i].y;
	   P[i].y = cos(value)*P[i].y-sin(value)*P[i].z;
	   P[i].z = sin(value)*tmp+cos(value)*P[i].z;
	 }
       break;
    }
}

Point Cube::center_of_cube()
{
  Point p1 = P[1];
  Point p2 = P[7];
  Point t  = vector(p1, p2);

  Point center = { p1.x + t.x/2,
		   p1.y + t.y/2,
		   p1.z + t.z/2,
		   0 };
  return center;
}

