// Esto es muy sucio //
#include "SDL2/SDL_opengl.h"

#include <SDL2/SDL.h>

typedef struct {
  GLenum Type;
  GLfloat M[16];
  struct Node *next;
  struct Node *inf;
} Node;

GLAPI void GLAPIENTRY glSetRender(SDL_Renderer *_renderer);

