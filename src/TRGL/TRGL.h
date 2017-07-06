#include "SDL2/SDL_opengl.h"

#include <SDL2/SDL.h>

struct Node {
  GLenum Type;
  GLfloat M[16];
  struct Node *next;
  struct Node *inf;
};


GLAPI void GLAPIENTRY glSetRender(SDL_Renderer *_renderer);

// Para cubrir la "magia" de SDL2
void SDL_TR_CreateRenderer(SDL_Window *gWindow);
void SDL_TR_SwapWindow(SDL_Window *gWindow);

// Apoyo matemático
void empty_matrixf(GLfloat M[16]);
