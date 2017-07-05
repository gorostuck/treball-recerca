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

GLAPI void GLAPIENTRY glMatrixMode(GLenum flags)
{
  /*
  if ((flags & GL_PROJECTION) == GL_PROJECTION) {
  }
  if ((flags & GL_MODELVIEW) == GL_MODELVIEW) {
    first = (Node *)malloc(sizeof(Node));
    first->next = NULL;
    first->inf  = NULL;
  }
  */
}

GLAPI void GLAPIENTRY glLoadIdentity()
{
  empty_matrixf(first->M);
}

GLAPI void GLAPIENTRY glClear(GLenum flags)
{
  
}

void SDL_TR_CreateRenderer(SDL_Window *gWindow)
{
  renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE); // También podría poner SDL_RENDERER_HARDWARE
}

void SDL_TR_SwapWindow(SDL_Window *gWindow)
{
  SDL_RenderPresent(renderer);
}

void empty_matrixf(GLfloat M[16])
{
  /* 
  for (int i = 0; i < 16; ++i)
    M[i] = 0.0f;
  */
}



