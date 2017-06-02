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

/*


    Point p1 = { -5, 5, 0, 0};
    Point p4 = { 5, -5, 0, 0};

    Point p2 = { 5, 5, 0, 0};
    Point p3 = { -5, -5, 0, 0};


    brush.draw_line(p1, p4);
    brush.draw_line(p2, p3);

    */
    Cube *cube = new Cube;
    Point P[8]={{ -10, 10, 20, 0}, { 10, 10, 20, 0}, { 10, -10, 20, 0}, { -10, -10, 20, 0},
                { -10, 10, 40, 0}, { 10, 10, 40, 0}, { 10, -10, 40, 0}, { -10, -10, 40, 0}};

    fill_cube(cube, P);
    translate_cube(cube, AXIS_Y, 10);

    float t, k = 10.; // Origen es (0,0,0); entonces punto real y vector director iguales
    Point O={0.,0.,0.,0.};
    /*
    //Traslaciones de 5 eje x
    for(int i = 0; i < 8; ++i)
    {
        P[i].x += 0;
        P[i].y += 0;
        P[i].z += 0;
    }
    */
    //float tmp;
    //Giro eje z angulo angz

    /*
    angz = 15;
    float tmp;
    for(int i = 0; i < 8; ++i)
    {
        tmp = P[i].x;
        P[i].x = cos(angz)*P[i].x+sin(angz)*P[i].y;
        P[i].y = -sin(angz)*tmp+cos(angz)*P[i].y;
    }
    */

    /*
    //Giro eje y angulo angy
    float angy = 0.1;
    int tmp;
    for(int i = 0; i < 8; ++i)
    {
        tmp = P[i].x;
        P[i].x = cos(angy)*P[i].x+sin(angy)*P[i].z;
        P[i].z = -sin(angy)*tmp+cos(angy)*P[i].z;
    }
    */

    /*
    //Giro eje x angulo angx
    float angx = 0.5;
    int tmp;
    for(int i = 0; i < 8; ++i)
    {
        tmp = P[i].y;
        P[i].y = cos(angx)*P[i].y+sin(angx)*P[i].z;
        P[i].z = -sin(angx)*tmp+cos(angx)*P[i].z;
    }
    */



    Point Q[8]; // Q es punto sobre plano de proyección
    for(int i = 0; i < 8; ++i)
    {
      t=(k-(cube->P[i].z)/(cube->P[i].z-O.z));
      Q[i].x = O.x + t*(cube->P[i].x-O.x);
      Q[i].y = O.y + t*(cube->P[i].y-O.y);

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



    screen.update();

    screen.wait_screen(10);
    return 1;
}

void render_cube(Cube *cube, Point O, float t, float k)
{
  
}
    
void fill_cube(Cube *cube, Point point[8])
{
  for (int i = 0; i < 8; ++i){
    cube->P[i] = point[i];
  }
}

void rotate_cube(Cube *cube, int axis, int value)
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

void translate_cube(Cube *cube, int axis, int value)
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

