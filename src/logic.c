/* Este archivo contiene las definiciones sobre la lógica de la simulación y la gestión de eventos */
#include "logic.h"

#include <SDL2/SDL.h>
#include "trgl_add.h"

SDL_Event event;

int max_x, max_y;
SDL_Window *window;
SDL_Renderer *renderer;


int logic_start()
{
  if (window_start())
    return 1;
  while (logic_loop());
  window_end();
  return 0;
  
}

int logic_loop()
{
  SDL_PollEvent(&event);
  if (event.type == SDL_WINDOWEVENT){
    switch (event.window.event){
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      window_update_size();
      break;
    }
  }
  if (event.type == SDL_KEYDOWN) {
    int key_pressed = event.key.keysym.sym;
    switch (key_pressed)
      {
      case SDLK_r:
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	break;
      case SDLK_g:
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	break;
      case SDLK_b:
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	break;
      case SDLK_ESCAPE:
	return 0;
	break;
      }
  }
  if (event.type == SDL_QUIT)
    return 0;



  
  SDL_RenderPresent(renderer);
  return 1;
}

int window_start()
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
  
#ifdef TRGL_MODE
  glSetRender(renderer);
#endif

  //glShadeModel( GL_SMOOTH );                         // Enable smooth shading 
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );              // Set the background black
  //glClearDepth( 1.0f );                                // Depth buffer setup
  //glEnable( GL_DEPTH_TEST );                           // Enables Depth Testing 
  //glDepthFunc( GL_LEQUAL );                          // The Type of Depth Test To Do
  /* END INIT GL */
    
  set_viewport(512, 512);

  max_x = DEFAULT_MAX_SCREEN_X;
  max_y = DEFAULT_MAX_SCREEN_Y;
  return 0;
}

void window_end()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void window_update_size()
{
  SDL_GetWindowSize(window, &max_x, &max_y);
  set_viewport(max_x, max_y);
  SDL_RenderPresent(renderer);
}

void set_viewport(int width, int height)
{
  /* Height / width ration */
    /* GLfloat ratio; */

    /* /\* Protect against a divide by zero *\/ */
    /* if ( height == 0 ) { */
    /*     height = 1; */
    /* } */

    // ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    //glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    //glMatrixMode( GL_PROJECTION );
    //glLoadIdentity( );

    /* Set our perspective */
    //gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    //glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    //glLoadIdentity( );
  
}
