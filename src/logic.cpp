/* Este archivo contiene las definiciones sobre la lógica

de la simulación y la gestión de eventos */
#include "logic.h"

#include <stdio.h>

#include "screen.h"
#include "brush.h"

SDL_Event event;
Screen screen;
Brush brush;
Point observer = {0., 0., 0., 0.};
float k = 0;
Cube *main_cube, *reset_cube;

int logic_start(void)
{

    if (screen.start_screen())
        return 1;
    brush.start_brush(&screen);

    /* inits */
    observer = { 0., 0., 0., 0.};
    main_cube = new Cube;
    reset_cube = new Cube;
            
    Point P[8]={{ -5, 5, 10, 0}, { 5, 5, 10, 0}, { 5, -5, 10, 0}, { -5, -5, 10, 0},
                { -5, 5, 20, 0}, { 5, 5, 20, 0}, { 5, -5, 20, 0}, { -5, -5, 20, 0}};
    fill_cube(reset_cube, P);
    fill_cube(main_cube, reset_cube->P);
    k = 5;

    while (logic_loop());
    screen.end_screen();

    delete main_cube;
    delete reset_cube;


    return 0;
}

int logic_loop(void)
{
    SDL_PollEvent(&event);
    if (event.type == SDL_WINDOWEVENT){
      switch (event.window.event){
      case SDL_WINDOWEVENT_SIZE_CHANGED:
	screen.update_size();
	break;
      }
    }
    if (event.type == SDL_QUIT)
      return 0;

    if (event.type == SDL_KEYDOWN)
      {
        int keyPressed = event.key.keysym.sym;

	switch (keyPressed)
	  {
	  case SDLK_q:
	    translate_cube(main_cube, AXIS_X, 0.1);
	    break;
	  case SDLK_a:
	    translate_cube(main_cube, AXIS_X, -0.1);
	    break;
	  case SDLK_w:
	      translate_cube(main_cube, AXIS_Y, 0.1);
	    break;
	  case SDLK_s:
	    translate_cube(main_cube, AXIS_Y, -0.1);
	    break;
	  case SDLK_e:
	    translate_cube(main_cube, AXIS_Z, 0.1);
	    break;
	  case SDLK_d:
	    translate_cube(main_cube, AXIS_Z, -0.1);
	    break;
	  case SDLK_r:
	    rotate_cube_local(main_cube, AXIS_X,  0.1);
	    break;
	  case SDLK_f:
	    rotate_cube_local(main_cube, AXIS_X, -0.1);
	    break;
	  case SDLK_t:
	    rotate_cube_local(main_cube, AXIS_Y,  0.1);
	    break;
	  case SDLK_g:
	    rotate_cube_local(main_cube, AXIS_Y, -0.1);
	    break;
	  case SDLK_y:
	    rotate_cube_local(main_cube, AXIS_Z,  0.1);
	    break;
	  case SDLK_h:
	    rotate_cube_local(main_cube, AXIS_Z, -0.1);
	    break;

	  case SDLK_SPACE:
	    fill_cube(main_cube, reset_cube->P);
	    break;

	  case SDLK_ESCAPE:
	    return 0;
	  }
	
      }

    
    // Draw time

    Color color_black = { 0, 0, 122, 255 };
    Color color_white = { 255, 255, 255, 255};

    brush.change_color(color_black);
    brush.draw_full();

    brush.change_color(color_white);

    render_cube(main_cube);

    // Finish draw
    
    screen.update();
    
    screen.wait_screen(10);
    return 1;
}

void render_cube(Cube *cube)
{
  float t;
  Point Q[8];

  for(int i = 0; i < 8; ++i)
  {
    t=(k-cube->P[i].z)/(cube->P[i].z-observer.z);
    Q[i].x = observer.x + t*(cube->P[i].x-observer.x);
    Q[i].y = observer.y + t*(cube->P[i].y-observer.y);

  }

  brush.draw_line(Q[0], Q[1]);
  brush.draw_line(Q[1], Q[2]);
  brush.draw_line(Q[2], Q[3]);
  brush.draw_line(Q[3], Q[0]);

  brush.draw_line(Q[4], Q[5]);
  brush.draw_line(Q[5], Q[6]);
  brush.draw_line(Q[6], Q[7]);
  brush.draw_line(Q[7], Q[4]);

  brush.draw_line(Q[0], Q[4]);
  brush.draw_line(Q[1], Q[5]);
  brush.draw_line(Q[2], Q[6]);
  brush.draw_line(Q[3], Q[7]);
  
}

void fill_cube(Cube *cube, Point point[8])
{
  for (int i = 0; i < 8; ++i){
    cube->P[i] = point[i];
  }
}

void rotate_cube(Cube *cube, int axis, float value)
{
  float tmp;
  switch (axis)
    {
    case AXIS_Z:
      for (int i = 0; i < 8; ++i)
	{
	  tmp = cube->P[i].x;
	  cube->P[i].x = cos(value)*cube->P[i].x+sin(value)*cube->P[i].y;
	  cube->P[i].y = -sin(value)*tmp+cos(value)*cube->P[i].y;
	}
      break;
    case AXIS_Y:
       for(int i = 0; i < 8; ++i)
	 {
	   tmp = cube->P[i].x;
	   cube->P[i].x = cos(value)*cube->P[i].x+sin(value)*cube->P[i].z;
	   cube->P[i].z = -sin(value)*tmp+cos(value)*cube->P[i].z;
	 }
       break;
    case AXIS_X:
       for(int i = 0; i < 8; ++i)
	 {
	   tmp = cube->P[i].y;
	   cube->P[i].y = cos(value)*cube->P[i].y+sin(value)*cube->P[i].z;
	   cube->P[i].z = -sin(value)*tmp+cos(value)*cube->P[i].z;
	 }
       break;
    }

}

void translate_cube(Cube *cube, int axis, float value)
{
  for (int i = 0; i < 8; ++i){
    switch (axis){
    case AXIS_X:
      cube->P[i].x += value;
      break;
    case AXIS_Y:
      cube->P[i].y += value;
      break;
    case AXIS_Z:
      cube->P[i].z += value;
      break;
    }
  }
}

Point translate_cube(Cube *cube, Point point)
{
  Point t = vector(center_of_cube(cube), point);
  for (int i = 0; i < 8; ++i)
    {
      cube->P[i].x += t.x;
      cube->P[i].y += t.y;
      cube->P[i].z += t.z;
    }
  return t;
  
}

Point vector(Point p1, Point p2)
{
  Point result = { p2.x - p1.x,
		   p2.y - p1.y,
		   p2.z - p1.z,
		   1 };
  return result;
}

Point center_of_cube(Cube *cube)
{
  Point p1 = cube->P[1];
  Point p2 = cube->P[7];

  Point center = { p1.x + (p2.x - p1.x)/2,
		   p1.y + (p2.y - p1.y)/2,
		   p1.z + (p2.z - p1.z)/2,
		   0 };
  return center;

}

void rotate_cube_local(Cube *cube, int axis, float value)
{
  
  Point origin = { 0., 0., 0., 0. };
  Point t = translate_cube(cube, origin);
  rotate_cube(cube, axis, value);
  for (int i = 0; i < 8; ++i)
    {
      cube->P[i].x -= t.x;
      cube->P[i].y -= t.y;
      cube->P[i].z -= t.z;
    }
}
