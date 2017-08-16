#include "Init.h"

#ifdef TRGL_MODE
#include "TRGL/TRGL.h"
#endif /* TRGL_MODE */

//The renderer
SDL_Renderer *renderer = NULL;

// Valores definidos en Execute.c
extern const size_t sizeof4GLuint;
extern const size_t sizeof4GLfloat;
extern const size_t sizeof16GLfloat;

// Definido en List.c
extern struct List *firstList, *currentList;

int init_window(void)
{
#ifdef TRGL_MODE
  return init_window_TRGL();
#else
  return init_window_openGL();
#endif /* TRGL_MODE */
}

int init_window_openGL()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return SDL_FALSE;
  }
  else {
    // Use OpenGL 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
    gWindow = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      return SDL_FALSE;
    } else {
      gContext = SDL_GL_CreateContext(gWindow);
      if (!initGL()) {
	printf("Unable to initialize OpenGL!");
	return SDL_FALSE;
      }
    }
  }
  return SDL_TRUE;
}

#ifdef TRGL_MODE
int init_window_TRGL()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return SDL_FALSE;
  }
  else {
    gWindow = SDL_CreateWindow("TRGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      return SDL_FALSE;
    }
    else {
      SDL_TR_CreateRenderer(gWindow);
      if (!initGL()) {
	printf("Unable to initialize TRGL!\n");
	return SDL_FALSE;
      }
    }
  }
  return SDL_TRUE;
}
#endif /* TRGL_MODE */

int initGL()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(1.f, 1.f, 1.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT);
	
  return SDL_TRUE;
}

void handleKeys(unsigned char key, int x, int y)
{
  if (key == 'q')
    {
      quit = SDL_TRUE;
    }
}


void close_window()
{
  //Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

#ifdef TRGL_MODE
  SDL_TR_Quit();
#else
  SDL_Quit();
#endif /* TRGL_MODE */
  

  //FreeStacks();
}

void swap_window()
{
#ifdef TRGL_MODE
  SDL_TR_SwapWindow();
#else
  SDL_GL_SwapWindow(gWindow);
#endif /* TRGL_MODE */
}


