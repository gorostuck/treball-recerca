/* Este archivo se debería de terminar por separar con el tiempo */
#include "TRGL.h"
#include "TRGL_math.h"

#include <stdio.h>
#include <stdlib.h>


#define REAL_W 12
#define REAL_X 0                       /*    [ REAL_X  PROJECTED_X  SCREEN_X  COLOR_R ]   */
#define REAL_Y 4                       /*    [ REAL_Y  PROJECTED_Y  SCREEN_X  COLOR_G ]   */
#define REAL_Z 8                       /*    [ REAL_Z  PROJECTED_Z         0  COLOR_B ]   */
#define PROJECTED_X 1                  /*    [      1            0         0  COLOR_A ]   */
#define PROJECTED_Y 5
#define PROJECTED_Z 9
#define SCREEN_X 2
#define SCREEN_Y 10
#define COLOR_R 3
#define COLOR_G 7
#define COLOR_B 11
#define COLOR_A 15


struct Node *first, *current, *temp;
SDL_Renderer *renderer;

GLAPI void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  first->M[COLOR_R] = red;
  first->M[COLOR_G] = green;
  first->M[COLOR_B] = blue;
  first->M[COLOR_A] = alpha;
  
  SDL_SetRenderDrawColor(renderer,
			 (int) red  * 255, (int) green * 255,
			 (int) blue * 255, (int) alpha * 255);
  SDL_RenderClear(renderer);
}

GLAPI void GLAPIENTRY glColor3f(GLclampf red, GLclampf green, GLclampf blue)
{
  first->M[COLOR_R] = red;
  first->M[COLOR_G] = green;
  first->M[COLOR_B] = blue;
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

  /* Asignación de coordenadas reales */
  temp->M[REAL_X] = x;
  temp->M[REAL_Y] = y;
  temp->M[REAL_Z] = z;
  temp->M[REAL_W] = 1;

  /* Ahora debería de calcular las proyecciones */
  
  /* Asignación de colores */
  temp->M[COLOR_R] = first->M[COLOR_R];
  temp->M[COLOR_G] = first->M[COLOR_G];
  temp->M[COLOR_B] = first->M[COLOR_B];
  temp->M[COLOR_A] = first->M[COLOR_A];

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

  /* Asignación de coordenadas reales */
  temp->M[REAL_X] = x;
  temp->M[REAL_Y] = y;
  temp->M[REAL_W] = 1;

  /* Ahora debería de calcular las proyecciones */

  /* Asignación de colores */
  temp->M[COLOR_R] = first->M[COLOR_R];
  temp->M[COLOR_G] = first->M[COLOR_G];
  temp->M[COLOR_B] = first->M[COLOR_B];
  temp->M[COLOR_A] = first->M[COLOR_A];

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
  SDL_SetRenderDrawColor(renderer,
  			 255, 255, 255, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer,
			 0, 0, 0, 0);
  int width, height;
  SDL_GetWindowSize(gWindow, &width, &height);
  GLfloat screen_matrix[16];
  /*
     [ delta_x/2             0   x_m + delta_x/2  0 ]
     [         0   - delta_y/2   y_m + delta_y/2  0 ]
     [         0             0                 1  0 ]
     [         0             0                 0  0 ] */

  /* Hay que cambiar esto con el tiempo pero por el momento, se asume que el programa ocupa toda la ventana */

  int x_M = width;
  int x_m = 0;
  int y_M = height;
  int y_m = 0;
  int delta_x = x_M - x_m;
  int delta_y = y_M - y_m;
  
  empty_matrixf(screen_matrix);
  screen_matrix[0] = (float)delta_x/2;
  screen_matrix[2] = (float)delta_x/2 + x_m;
  screen_matrix[5] = (float)-(delta_y/2);
  screen_matrix[6] = (float)delta_y/2 + y_m;
  screen_matrix[10] = 1;


  /* Primero se calcula la posición en la pantalla de todos los puntos */
  for (current=first;current!=NULL;current=current->next){
    for (temp=current->inf;temp!=NULL;temp=temp->inf){
      simple_multiply_matrixf(temp->M, screen_matrix);
    }
  }

  /* Ahora se pintan en la pantalla */
  int state=0;
  struct Node *mem1;
  for (current=first;current!=NULL;current=current->next){
    for (temp=current->inf;temp!=NULL;temp=temp->inf){
      if (current->Type==GL_QUADS) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	if (state==3) {
	  SDL_RenderDrawLine(renderer,
			     temp->M[SCREEN_X], temp->M[SCREEN_Y],
			     mem1->M[SCREEN_X], mem1->M[SCREEN_Y]);
	  state = 0;
	}
	else {
	  SDL_RenderDrawLine(renderer,
			     temp->M[SCREEN_X], temp->M[SCREEN_Y],
			     temp->inf->M[SCREEN_X], temp->inf->M[SCREEN_Y]);
	  if (state==0)
	    mem1 = temp;
	  ++state;
	}
      }
    }
  }

  /* Liberar toda la estructura */
  struct Node *t1, *t2;
  for(current=first->next;current!=NULL;){
    for(temp=current->inf;temp!=NULL;){
      t2 = temp;
      temp = temp->inf;
      free(t2);
    }
    t1 = current;
    current = current->next;
    free(t1);
  }
  current = first;
  temp = NULL;
  SDL_RenderPresent(renderer);
}



