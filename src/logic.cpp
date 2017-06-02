/* Este archivo contiene las definiciones sobre la lógica

de la simulación y la gestión de eventos */
#include "logic.h"

#include <stdio.h>

#include "screen.h"
#include "brush.h"

SDL_Event event;
Screen screen;
Brush brush;

int logic_start(void)
{

    if (screen.start_screen())
        return 1;
    brush.start_brush(&screen);

    /* inits */
    main_cube = new Cube;
    reset_cube = new Cube;
    Point P[8]={{ -10, 10, 20, 0}, { 10, 10, 20, 0}, { 10, -10, 20, 0}, { -10, -10, 20, 0},
                { -10, 10, 40, 0}, { 10, 10, 40, 0}, { 10, -10, 40, 0}, { -10, -10, 40, 0}};
    fill_cube(reset_cube, P);
    fill_cube(main_cube, reset_cube->P);
    k = 10;

    while (logic_loop());
    screen.end_screen();

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

// Draw time:

    Color color_black = { 0, 0, 0, 255 };
    Color color_white = { 255, 255, 255, 255};

    brush.change_color(color_black);
    brush.draw_full();

    brush.change_color(color_white);

    rotate_cube(main_cube, AXIS_Z, 0.01);
    render_cube(main_cube);
    
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

