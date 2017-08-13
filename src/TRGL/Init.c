#include "Init.h"

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
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    //success = SDL_FALSE;
    return SDL_FALSE;
  }
  else {
    gWindow = SDL_CreateWindow("TRGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      //success = SDL_FALSE;
      return SDL_FALSE;
    }
    else {
      SDL_TR_CreateRenderer(gWindow);
      if (!initGL()) {
	printf("Unable to initialize TRGL!\n");
	//success = SDL_FALSE;
	return SDL_FALSE;
      }
    }
  }

  return SDL_TRUE;
}

int initGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
	
  //	glClearColor(1.f, 0.5f, 0.25f, 1.f);
	
  return SDL_TRUE;
}

void handleKeys(unsigned char key, int x, int y)
{
  if (key == 'q')
    {
      quit = SDL_TRUE;
    }
}

GLboolean SDL_TR_CreateRenderer(SDL_Window *_gWindow)
{
  renderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_SOFTWARE); // También podría poner SDL_RENDERER_HARDWARE

  if (renderer == NULL)
    return SDL_FALSE;

  CreateFirstList();

  CreateFirsStack();

  InitMatrix();

  return SDL_TRUE;
}

void close_window()
{
  //Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();

  FreeAllLists();
  //FreeStacks();
}

void InitMatrix(void)
{
  memcpy(firstList->firstNode->Matrix, Identity, sizeof16GLfloat);
}
