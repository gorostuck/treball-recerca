/* Este archivo se debería de terminar por separar con el tiempo */
#include "TRGL.h"
#include "TRGL_math.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>


struct Node *first, *current, *temp;
SDL_Renderer *renderer;

float *MAT, M_MAT[16], P_MAT[16], T_MAT[16], C_MAT[16];
GLenum MAT_NAME;

GLAPI void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  first->Color[0] = red;
  first->Color[1] = green;
  first->Color[2] = blue;
  first->Color[3] = alpha;


  SDL_SetRenderDrawColor(renderer,
			 (int) red  * 255, (int) green * 255,
			 (int) blue * 255, (int) alpha * 255);
  SDL_RenderClear(renderer);

}

GLAPI void GLAPIENTRY glColor3f(GLclampf red, GLclampf green, GLclampf blue)
{
  first->Color[0] = red;
  first->Color[1] = green;
  first->Color[2] = blue;
 }

GLAPI void GLAPIENTRY glBegin(GLenum mode)
{
  current->next = malloc(sizeof(struct Node));
  current = current->next;
  current->Type = mode;
  current->next = NULL;
  current->inf  = NULL;
}

GLAPI void GLAPIENTRY glVertex(float x, float y, float z)
{
  if (current->inf == NULL) {
    current->inf = malloc(sizeof(struct Node));
    temp = current->inf;
  } else {
    temp->inf = malloc(sizeof(struct Node));
    temp = temp->inf;
  }

  /* Asignación de coordenadas reales */
  temp->Real[0] = x;
  temp->Real[1] = y;
  temp->Real[2] = z;
  temp->Real[3] = 1;

  /* Ahora debería de calcular las proyecciones */

  /* Asignación de colores */
  temp->Color[0] = first->Color[0];
  temp->Color[1] = first->Color[1];
  temp->Color[2] = first->Color[2];
  temp->Color[3] = first->Color[3];

  temp->next = NULL;
  temp->inf  = NULL;
}

GLAPI void GLAPIENTRY glVertex2f(float x, float y)
{
  if (current->inf == NULL) {
    current->inf = malloc(sizeof(struct Node));
    temp = current->inf;
  } else {
    temp->inf = malloc(sizeof(struct Node));
    temp = temp->inf;
  }

  /* Asignación de coordenadas reales */
  temp->Real[0] = x;
  temp->Real[1] = y;
  temp->Real[2] = 0;
  temp->Real[3] = 1;

  float REAL[16] = { 1, 0, 0, x,
		     0, 1, 0, y,
		     0, 0, 1, 0,
		     0, 0, 0, 1};

  float NEW_REAL[16];
  multiply_matrix_4x4_1x4(REAL, MAT, NEW_REAL);
  
  temp->Real[0]=NEW_REAL[3];
  temp->Real[1]=NEW_REAL[7];
  temp->Real[2]=NEW_REAL[11];
  temp->Real[3]=NEW_REAL[15];

  //printf("%f, %f, %f, %f\n", temp->Real[X], temp->Real[Y], temp->Real[Z], temp->Real[W]);

  /* Ahora debería de calcular las proyecciones */
  temp->Projected[0] = temp->Real[0];
  temp->Projected[1] = temp->Real[1];
  temp->Projected[2] = 1;

  /* Asignación de colores */
  temp->Color[0] = first->Color[0];
  temp->Color[1] = first->Color[1];
  temp->Color[2] = first->Color[2];
  temp->Color[3] = first->Color[3];

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
  current = first;
  MAT = M_MAT;
  first->Color[0] = 0;
}

GLAPI void GLAPIENTRY glMatrixMode(GLenum flags)
{
  MAT_NAME = flags;
  if ((flags & GL_MODELVIEW) == GL_MODELVIEW)
    MAT = M_MAT;
  if ((flags & GL_PROJECTION) == GL_PROJECTION)
    MAT = P_MAT;
  if ((flags & GL_TEXTURE) == GL_TEXTURE)
    MAT = T_MAT;
  if ((flags & GL_COLOR) == GL_COLOR)
    MAT = C_MAT;
}

GLAPI void GLAPIENTRY glLoadIdentity()
{
  MAT[0] = 1;
  MAT[1] = 0;
  MAT[2] = 0;
  MAT[3] = 0;
  MAT[4] = 0;
  MAT[5] = 1;
  MAT[6] = 0;
  MAT[7] = 0;
  MAT[8] = 0;
  MAT[9] = 0;
  MAT[10] = 1;
  MAT[11] = 0;
  MAT[12] = 0;
  MAT[13] = 0;
  MAT[14] = 0;
  MAT[15] = 1;
}

GLAPI void GLAPIENTRY glClear(GLenum flags)
{

}

void SDL_TR_CreateRenderer(SDL_Window *gWindow)
{
  renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE); // También podría poner SDL_RENDERER_HARDWARE
  first = malloc(sizeof(struct Node));
  first->next = NULL;
  first->inf  = NULL;
  current = first;
  MAT = M_MAT;
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
  float screen_matrix[9];
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
      multiply_matrix_3x3_1x3(screen_matrix, temp->Projected, temp->Screen);
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
			     temp->Screen[0], temp->Screen[1],
			     mem1->Screen[0], mem1->Screen[1]);
	  state = 0;
	}
	else {
	  SDL_RenderDrawLine(renderer,
			     temp->Screen[0], temp->Screen[1],
			     temp->inf->Screen[0], temp->inf->Screen[1]);
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

GLAPI void GLAPIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z )
{
  const float m[16] = { 1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1 };
  glMultMatrixf(m);
}

GLAPI void GLAPIENTRY glRotatef(GLfloat angle,
				GLfloat x,
				GLfloat y,
				GLfloat z)
{
  GLfloat c = cos(angle);
  GLfloat s = sin(angle);

  const float m[16] = {   pow(x,2)*(1-c)+c, x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0,
			  y*x*(1-c)+z*s,  pow(y,2)*(1-c)+c,  y*z*(1-c)-x*s, 0,
			  x*z*(1-c)-y*s, y*z*(1-c)+x*s,   pow(z,2)*(1-c)+c, 0,
			  0,             0,              0, 1 };
  glMultMatrixf(m);
}
 
GLAPI void GLAPIENTRY glMultMatrixf( const GLfloat *m )
{
  float NEW_MAT[16];
  multiply_matrix_4x4_1x4(MAT, m, NEW_MAT);
  copy_matrix4x4f(NEW_MAT, MAT);
}

void gluPerspective(GLdouble fovy,
		    GLdouble aspect,
		    GLdouble zNear,
		    GLdouble zFar)
{
}

void glFrustrum(GLdouble left,
		GLdouble right,
		GLdouble bottom,
		GLdouble top,
		GLdouble nearVal,
		GLdouble farVal)
{
}

GLAPI void GLAPIENTRY glOrtho( GLdouble left, GLdouble right,
                                 GLdouble bottom, GLdouble top,
                                 GLdouble near_val, GLdouble far_val )
{
}
