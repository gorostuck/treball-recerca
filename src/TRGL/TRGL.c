/* Este archivo se debería de terminar por separar con el tiempo */
#include "TRGL.h"

#include <stdio.h>
#include <stdlib.h>

#define R_X 0
#define R_Y 1
#define R_Z 2
#define R_W 3
#define P_X 4
#define P_Y 5
#define P_Z 6
#define P_W 7
#define S_X 8
#define S_Y 9


struct Node *first, *current, *temp;
SDL_Renderer *renderer;

GLAPI void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  SDL_SetRenderDrawColor(renderer,
			 (int) red  * 255, (int) green * 255,
			 (int) blue * 255, (int) alpha * 255);
  SDL_RenderClear(renderer);
}

GLAPI void GLAPIENTRY glColor3f(GLclampf red, GLclampf green, GLclampf blue)
{
  SDL_SetRenderDrawColor(renderer, (int) red * 255, (int) green * 255, (int) blue * 255, 0);
}

GLAPI void GLAPIENTRY glBegin(GLenum mode)
{
  current->next = malloc(sizeof(struct Node));
  current = current->next;
  current->Type = mode;
  current->next = NULL;
  current->inf  = NULL;
}

GLAPI void GLAPIENTRY glVertex(GLfloat x, GLfloat y, GLfloat z)
{
  if (current->inf == NULL) {
    current->inf = malloc(sizeof(struct Node));
    temp = current->inf;
  } else {
    temp->inf = malloc(sizeof(struct Node));
    temp = temp->inf;
  }
  if (first->next==NULL)

  temp->M[R_X] = x;
  temp->M[R_Y] = y;
  temp->M[R_Z] = z;

  temp->next = NULL;
  temp->inf  = NULL;
}

GLAPI void GLAPIENTRY glVertex2f(GLfloat x, GLfloat y)
{
  if (current->inf == NULL) {
    current->inf = malloc(sizeof(struct Node));
    temp = current->inf;
  } else {
    temp->inf = malloc(sizeof(struct Node));
    temp = temp->inf;
  }
  temp->M[R_X] = x;
  temp->M[R_Y] = y;

  temp->next = NULL;
  temp->inf  = NULL;
}

GLAPI void GLAPIENTRY glEnd ()
{
  current = current->next;
  current = NULL;
}

GLAPI void GLAPIENTRY glSetRender(SDL_Renderer *_renderer)
{
  renderer = _renderer;
  first = malloc(sizeof(struct Node));
  first->next = NULL;
  first->inf  = NULL;
  current = first->next;
}

GLAPI void GLAPIENTRY glMatrixMode(GLenum flags)
{
  if ((flags & GL_PROJECTION) == GL_PROJECTION) {
  }
  if ((flags & GL_MODELVIEW) == GL_MODELVIEW) {
    first = malloc(sizeof(struct Node));
    first->next = NULL;
    first->inf  = NULL;
    current = first;
  }
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
  // printf("x: %f", first->next->inf->M[R_X]);
  /* Testeo */
  for (current=first;current!=NULL;current=current->next){
    for(temp=current->inf;temp!=NULL;temp=temp->inf){
      printf("x: %f, y: %f, z: %f\n", temp->M[R_X], temp->M[R_Y], current->M[R_Z]);
    }
  }
  
  SDL_RenderPresent(renderer);
}

void empty_matrixf(GLfloat M[16])
{
  /*
     for (int i = 0; i < 16; ++i)
     M[i] = 0.0f;
  */
}



