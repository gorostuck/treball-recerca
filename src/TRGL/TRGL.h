// Esto es muy sucio //
#include "trgl.h"

#define TRGL_MODE

#include <SDL2/SDL.h>

typedef struct {
  GLenum Type;
  GLfloat M[16];
  struct Node *next;
  struct Node *inf;
} Node;

GLAPI void GLAPIENTRY glSetRender(SDL_Renderer *_renderer);

