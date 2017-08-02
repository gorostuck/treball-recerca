#include "SDL2/SDL_opengl.h"

#include <SDL2/SDL.h>

struct Node {
  GLenum Type;
  GLfloat Real[4];
  GLfloat Projected[4];
  GLfloat Screen[3];
  GLfloat Color[4];
  struct Node *next;
  struct Node *inf;
};


#define X 0
#define Y 1
#define Z 2
#define W 3
#define R 0
#define G 1
#define B 2
#define A 3

GLAPI void GLAPIENTRY glSetRender(SDL_Renderer *_renderer);

// Para cubrir la "magia" de SDL2
void SDL_TR_CreateRenderer(SDL_Window *gWindow);
void SDL_TR_SwapWindow(SDL_Window *gWindow);

