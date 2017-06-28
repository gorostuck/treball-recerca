#include "screen.h"

#include <SDL2/SDL.h>
#include "trgl.h"

int max_x, max_y;
SDL_Window *window;
SDL_Renderer *renderer;

int screen_start(void)
{
  if (SDL_Init(SDL_INIT_VIDEO)){
    printf("SDL no se ha podido iniciar correctamente: %s\n", SDL_GetError());
    return 1;
  }

  if (SDL_CreateWindowAndRenderer(DEFAULT_MAX_SCREEN_X,DEFAULT_MAX_SCREEN_Y,
				  SDL_WINDOW_RESIZABLE, &window, &renderer)){
    if (window == NULL){
        printf("La ventana no se ha creado con éxito: %s\n", SDL_GetError());
        return 1;
    } if (renderer == NULL) {
        printf("El renderer no se ha creado con éxito: %s\n", SDL_GetError());
    }
  }

  /* START INIT GL */
  glShadeModel( GL_SMOOTH );                           // Enable smooth shading 
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );              // Set the background black
  glClearDepth( 1.0f );                                // Depth buffer setup
  glEnable( GL_DEPTH_TEST );                           // Enables Depth Teting 
  glDepthFunc( GL_LEQUAL );                            // The Type of Depth Test To Do
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ); // Really Nice Perspective Calculations
  /* END INIT GL */
    
  screen_set_viewport(512, 512);
  screen_display_render();

  max_x = DEFAULT_MAX_SCREEN_X;
  max_y = DEFAULT_MAX_SCREEN_Y;
  return 0;
}

int screen_end(void)
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
 
  return 0;
}

void screen_update_size()
{
  SDL_GetWindowSize(window, &max_x, &max_y);
  screen_set_viewport(max_x, max_y);
  screen_update();
}

void screen_change_color(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void screen_draw_full()
{
  SDL_RenderClear(renderer);
}

void screen_draw_point(int x, int y)
{
  SDL_RenderDrawPoint(renderer, x, y);
}

void screen_draw_line(int begin_x, int begin_y, int end_x, int end_y)
{
  SDL_RenderDrawLine(renderer, begin_x, begin_y, end_x, end_y);
}

void screen_update()
{
  screen_display_render();
}

int screen_set_viewport(int width, int height)
{
 /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if ( height == 0 ) {
        height = 1;
    }

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return 1; 
}

void screen_display_render(void)
{
      /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );

    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glTranslatef( 3.0f, 0.0f, 0.0f );

    glBegin( GL_QUADS );                /* Draw A Quad */
      glVertex3f( -1.0f,  1.0f, 0.0f ); /* Top Left */
      glVertex3f(  1.0f,  1.0f, 0.0f ); /* Top Right */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
    glEnd( );                           /* Done Drawing The Quad */
    
    SDL_RenderPresent(renderer);
}
