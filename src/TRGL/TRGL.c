/* Este archivo se debería de terminar por separar con el tiempo */
#include "TRGL.h"
#include "TRGL_math.h"

#include <stdio.h>
#include <stdlib.h>


struct Node *first, *current, *temp;
SDL_Renderer *renderer;

GLAPI void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  first->Color[R] = red;
  first->Color[G] = green;
  first->Color[B] = blue;
  first->Color[A] = alpha;
  
  SDL_SetRenderDrawColor(renderer,
			 (int) red  * 255, (int) green * 255,
			 (int) blue * 255, (int) alpha * 255);
  SDL_RenderClear(renderer);
}

GLAPI void GLAPIENTRY glColor3f(GLclampf red, GLclampf green, GLclampf blue)
{
  first->Color[R] = red;
  first->Color[G] = green;
  first->Color[B] = blue;
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
  temp->Real[X] = x;
  temp->Real[Y] = y;
  temp->Real[Z] = z;
  temp->Real[W] = 1;

  /* Ahora debería de calcular las proyecciones */
  
  /* Asignación de colores */
  temp->Color[R] = first->Color[R];
  temp->Color[G] = first->Color[G];
  temp->Color[B] = first->Color[B];
  temp->Color[A] = first->Color[A];

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
  temp->Real[X] = x;
  temp->Real[Y] = y;
  temp->Real[Z] = 1;

  /* Ahora debería de calcular las proyecciones */

  /* Asignación de colores */
  temp->Color[R] = first->Color[R];
  temp->Color[G] = first->Color[G];
  temp->Color[B] = first->Color[B];
  temp->Color[A] = first->Color[A];

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
  empty_matrix(first->Real,3);
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
  GLfloat screen_matrix[9];
  /*
     [ delta_x/2             0   x_m + delta_x/2  ]
     [         0   - delta_y/2   y_m + delta_y/2  ]
     [         0             0                 1  ] */

  int x_M = width;
  int x_m = 0;
  int y_M = height;
  int y_m = 0;
  int delta_x = x_M - x_m;
  int delta_y = y_M - y_m;
  
  empty_matrix(screen_matrix,9);
  
  screen_matrix[0] = (float)delta_x/2;
  screen_matrix[2] = (float)delta_x/2 + x_m;
  screen_matrix[4] = (float)-(delta_y/2);
  screen_matrix[5] = (float)delta_y/2 + y_m;
  screen_matrix[8] = 1;


  /* Primero se calcula la posición en la pantalla de todos los puntos */
  for (current=first;current!=NULL;current=current->next){
    for (temp=current->inf;temp!=NULL;temp=temp->inf){
      // Aquí debería de ser projected
      multiply_matrix_3x3_1x3(screen_matrix, temp->Real, temp->Screen);
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
			     temp->Screen[X], temp->Screen[Y],
			     mem1->Screen[X], mem1->Screen[Y]);
	  state = 0;
	}
	else {
	  SDL_RenderDrawLine(renderer,
			     temp->Screen[X], temp->Screen[Y],
			     temp->inf->Screen[X], temp->inf->Screen[Y]);
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



