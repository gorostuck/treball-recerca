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
Cube main_cube, reset_cube;

int logic_start(void)
{

    if (screen.start_screen())
        return 1;
    brush.start_brush(&screen);

    /* inits */
    Point P[8]={{ -5, 5, 10, 0}, { 5, 5, 10, 0}, { 5, -5, 10, 0}, { -5, -5, 10, 0},
                { -5, 5, 20, 0}, { 5, 5, 20, 0}, { 5, -5, 20, 0}, { -5, -5, 20, 0}};

    main_cube = Cube(P);
    reset_cube = Cube(P);

    k = 5;

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

    if (event.type == SDL_KEYDOWN)
      {
        int keyPressed = event.key.keysym.sym;

	switch (keyPressed)
	  {
	  case SDLK_q:
	    main_cube.translate(AXIS_X, 0.1);
	    break;
	  case SDLK_a:
	    main_cube.translate(AXIS_X, -0.1);
	    break;
	  case SDLK_w:
	    main_cube.translate(AXIS_Y, 0.1);
	    break;
	  case SDLK_s:
	    main_cube.translate(AXIS_Y, -0.1);
	    break;
	  case SDLK_e:
	    main_cube.translate(AXIS_Z, 0.1);
	    break;
	  case SDLK_d:
	    main_cube.translate(AXIS_Z, -0.1);
	    break;
	  case SDLK_r:
	    main_cube.rotate_local(AXIS_X,  0.1);
	    break;
	  case SDLK_f:
	    main_cube.rotate_local(AXIS_X, -0.1);
	    break;
	  case SDLK_t:
	    main_cube.rotate_local(AXIS_Y,  0.1);
	    break;
	  case SDLK_g:
	    main_cube.rotate_local(AXIS_Y, -0.1);
	    break;
	  case SDLK_y:
	    main_cube.rotate_local(AXIS_Z,  0.1);
	    break;
	  case SDLK_h:
	    main_cube.rotate_local(AXIS_Z, -0.1);
	    break;

	  case SDLK_SPACE:
	    main_cube = Cube(reset_cube.P);
	    break;

	  case SDLK_ESCAPE:
	    return 0;
	  }

      }


    // Draw time

    Color color_black = { 0, 0, 0, 255 };
    Color color_white = { 255, 255, 255, 255};

    brush.change_color(color_white);
    brush.draw_full();

    brush.change_color(color_black);

    render_cube(main_cube.P);

    // Finish draw

    screen.update();

    screen.wait_screen(5);
    return 1;
}

void render_cube(Point P[8])
{
  float t;
  Point Q[8];

  for(int i = 0; i < 8; ++i)
  {
    t=(k-P[i].z)/(P[i].z-observer.z);
    Q[i].x = observer.x + t*(P[i].x-observer.x);
    Q[i].y = observer.y + t*(P[i].y-observer.y);

  }

  int f;
  Point u, v;
  { /* Cara 1 P1P2 x P2P3 */

    u = vector(P[0], P[1]);
    v = vector(P[1], P[2]);

    f = (u.x * v.y - u.y * v.x);

    if (f > 0) {
      brush.draw_line(Q[0], Q[1]);
      brush.draw_line(Q[1], Q[2]);
      brush.draw_line(Q[2], Q[3]);
      brush.draw_line(Q[3], Q[0]);
    } else {
      brush.draw_line_alt(Q[0], Q[1], 4);
      brush.draw_line_alt(Q[1], Q[2], 4);
      brush.draw_line_alt(Q[2], Q[3], 4);
      brush.draw_line_alt(Q[3], Q[0], 4);
    }
  }

  { /* Cara 2 P8P7 x P7P6 */

    u = vector(P[7], P[6]);
    v = vector(P[6], P[5]);

    f = (u.x * v.y - u.y * v.x);

    if (f > 0) {
      brush.draw_line(Q[4], Q[5]);
      brush.draw_line(Q[5], Q[6]);
      brush.draw_line(Q[6], Q[7]);
      brush.draw_line(Q[7], Q[4]);
    } else {
      brush.draw_line_alt(Q[4], Q[5], 4);
      brush.draw_line_alt(Q[5], Q[6], 4);
      brush.draw_line_alt(Q[6], Q[7], 4);
      brush.draw_line_alt(Q[7], Q[4], 4);
    }
  }

  { /* Cara 3 P2P6 x P5P6 */

    u = vector(P[1], P[4]);
    v = vector(P[4], P[5]);

    f = (u.x * v.y - u.y * v.x);

    if (f > 0) {
      brush.draw_line(Q[0], Q[4]);
      brush.draw_line(Q[4], Q[5]);
      brush.draw_line(Q[5], Q[1]);
      brush.draw_line(Q[1], Q[0]);
    } else {
      brush.draw_line_alt(Q[0], Q[4], 4);
      brush.draw_line_alt(Q[4], Q[5], 4);
      brush.draw_line_alt(Q[5], Q[1], 4);
      brush.draw_line_alt(Q[1], Q[0], 4);

    }
  }

  { /* Cara 4 P1P4 x P4P8 */

    u = vector(P[0], P[3]);
    v = vector(P[3], P[7]);

    f = (u.x * v.y - u.y * v.x);

    if (f > 0) {
      brush.draw_line(Q[0], Q[3]);
      brush.draw_line(Q[3], Q[7]);
      brush.draw_line(Q[7], Q[4]);
      brush.draw_line(Q[4], Q[0]);
    } else {
      brush.draw_line_alt(Q[0], Q[3], 4);
      brush.draw_line_alt(Q[3], Q[7], 4);
      brush.draw_line_alt(Q[7], Q[4], 4);
      brush.draw_line_alt(Q[4], Q[0], 4);
    }
  }

  { /* Cara 5 P4P3 x P3P7 */

    u = vector(P[3], P[2]);
    v = vector(P[2], P[6]);

    f = (u.x * v.y - u.y * v.x);

    if (f > 0) {
      brush.draw_line(Q[3], Q[2]);
      brush.draw_line(Q[2], Q[6]);
      brush.draw_line(Q[6], Q[7]);
      brush.draw_line(Q[7], Q[3]);
    } else {
      brush.draw_line_alt(Q[3], Q[2], 4);
      brush.draw_line_alt(Q[2], Q[6], 4);
      brush.draw_line_alt(Q[6], Q[7], 4);
      brush.draw_line_alt(Q[7], Q[3], 4);
    }
  }

  { /* Cara 6 P2P6 x P6P7 */

    u = vector(P[1], P[5]);
    v = vector(P[5], P[6]);

    f = (u.x * v.y - u.y * v.x);

    if (f > 0) {
      brush.draw_line(Q[1], Q[5]);
      brush.draw_line(Q[5], Q[6]);
      brush.draw_line(Q[6], Q[2]);
      brush.draw_line(Q[2], Q[1]);
    } else {
      brush.draw_line_alt(Q[1], Q[5], 4);
      brush.draw_line_alt(Q[5], Q[6], 4);
      brush.draw_line_alt(Q[6], Q[2], 4);
      brush.draw_line_alt(Q[2], Q[1], 4);
    }
  }

}


/* C1 -> P1P2P3P4 -> P1P2 P2P3
   C2 -> P8P7P6P5 -> P8P7 P7P6
   C3 -> P2P6P7P3 -> P2P6 P6P7
   C4 -> P1P4P8P5 -> P1P4 P4P8
   C5 -> P4P3P7P8 -> P4P3 P3P7
   C6 -> P1P5P6P2 -> P1P5 P5P6

Producto vectorial: solo importa k

Producto vectorial = k(u1*v2-u2*v1)

Si el factor por k es mayor a 0, la cara no se dibuja. */
