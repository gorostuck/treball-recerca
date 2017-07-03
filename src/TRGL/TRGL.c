/* Este archivo se debería de terminar por separar con el tiempo */
#include "TRGL.h"

#include <stdio.h>
#include <stdlib.h>

Node *first, *current, *temp;
SDL_Renderer *renderer;

GLAPI void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  SDL_SetRenderDrawColor(renderer,
			 (int) red  * 255, (int) green * 255,
			 (int) blue * 255, (int) alpha * 255);
  SDL_RenderClear(renderer);
}

GLAPI void GLAPIENTRY glBegin(GLenum mode) { }

GLAPI void GLAPIENTRY glVertex(GLfloat x, GLfloat y, GLfloat z) { }

GLAPI void GLAPIENTRY glEnd () { }

GLAPI void GLAPIENTRY glSetRender(SDL_Renderer *_renderer)
{
  renderer = _renderer;
  first = (Node *)malloc(sizeof(Node));
  first->next = NULL;
  first->inf  = NULL;
}




  
