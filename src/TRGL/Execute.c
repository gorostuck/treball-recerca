#include "Execute.h"

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "Node.h"
#include "List.h"
#include "Scanner.h"
#include "Stack.h"
#include "Matrix.h"

const size_t sizeof4GLuint = 4 * sizeof(GLuint);
const size_t sizeof4GLfloat = 4 * sizeof(GLfloat);
const size_t sizeof16GLfloat = 16 * sizeof(GLfloat);

// Definido en List.c
extern struct List *firstList, *currentList;

// Definido en Stack.c
extern struct Stack *firstStack, *currentStack;

struct Node *currentNode;

GLfloat *MatrixMode;

// Definido en Stack.c
extern const GLfloat Identity[16];

//Definido en init.c
extern SDL_Renderer *renderer;

GLboolean SDL_TR_SwapWindow(void)
{
  //static clock_t t_ini, t_fin;
  //double secs;
  //static double fps = 1. / 36.;
  //static GLboolean first = GL_FALSE;

  //if (first == GL_FALSE) {
  //	t_ini = clock();
  //	first = GL_TRUE;
  //}
  //t_fin = clock();

  //secs = fps - (double)(t_fin - t_ini) / CLOCKS_PER_SEC;

  //if (secs > 0)
  //	SDL_Delay((Uint32)(secs * 1000));
  //t_ini = t_fin;
  //glClearColor(1.f, 0.5f, 0.25f, 1.f);

  //currentNode = firstList->currentNode;

  currentList = firstList;

  for (currentNode = firstList->firstNode->Next; currentNode != NULL; currentNode = currentNode->Next) {
    switch (currentNode->Type) {
    case COLOR:
      memcpy(currentStack->Color, currentNode->Color, sizeof4GLuint);
      break;
    case NORMAL:
      memcpy(currentStack->Normal, currentNode->Normal, sizeof4GLfloat);
      break;
      //	case GL_POINTS:
      //		//        SDL_TR_Points();
      //		break;
    case GL_LINES:
      SDL_TR_Lines();
      break;
    case GL_LINE_LOOP:
      SDL_TR_Line_loop();
      break;
    case GL_TRIANGLES:
      SDL_TR_Triangles();
      break;
    case GL_QUADS:
      SDL_TR_Quads();
      break;
    case GL_POLYGON:
      SDL_TR_Poligon();
      break;
    case ORTHO:
    case FRUSTUM:
      Multiplicacion4x4(currentStack->Projection, currentNode->Matrix, currentStack->Projection);
      Multiplicacion24x4(currentStack->Viewport, currentStack->Projection, currentStack->Model, currentStack->MVP);
      break;
    case CLEARCOLOR:
      SDL_SetRenderDrawColor(renderer, currentNode->Color[0], currentNode->Color[1], currentNode->Color[2], currentNode->Color[3]);
      SDL_RenderClear(renderer);
      break;
    case GL_MATRIX_MODE:
      break;
    case GL_MODELVIEW:
      MatrixMode = currentStack->Model;
      break;
    case GL_PROJECTION:
      MatrixMode = currentStack->Projection;
      break;
    case GL_TEXTURE:
      break;

    case LOADIDENTITY:
      memcpy(MatrixMode, Identity, sizeof16GLfloat);
      if (MatrixMode == currentStack->Model)
	Inverse4x4(currentStack->Model, currentStack->NormalMatrix);
      Multiplicacion24x4(currentStack->Viewport, currentStack->Projection, currentStack->Model, currentStack->MVP);
      break;
      //	case LOADMATRIX:

      //		break;
      //	case MULTMATRIX:

      //		break;
    case MODEL:
      Multiplicacion4x4(currentStack->Model, currentNode->Matrix, currentStack->Model);
      Inverse4x4(currentStack->Model, currentStack->NormalMatrix);
      Multiplicacion24x4(currentStack->Viewport, currentStack->Projection, currentStack->Model, currentStack->MVP);
      break;
    case VIEWPORT:
      memcpy(currentStack->Viewport, currentNode->Matrix, sizeof16GLfloat);
      Multiplicacion24x4(currentStack->Viewport, currentStack->Projection, currentStack->Model, currentStack->MVP);
      break;
      //	case PUSHMATRIX:

      //		break;
      //	case POPMATRIX:

      //		break;
    default:
      break;
    }
  }
  SDL_RenderPresent(renderer);

  FreeFirstList();

  return SDL_TRUE;
}

GLboolean SDL_TR_Lines(void)
{
  GLfloat Point[4], Point2[4];

  for (currentNode = currentNode->Next; currentNode->Type == COLOR || currentNode->Type == NORMAL; currentNode = currentNode->Next) {
    switch (currentNode->Type)
      {
      case NORMAL:
	memcpy(currentStack->Normal, currentNode->Normal, sizeof4GLfloat);
	break;
      case COLOR:
	memcpy(currentStack->Color, currentNode->Color, sizeof4GLuint);
	break;
      default:
	break;
      }
  }
  MatrixxPoint4x4(currentStack->MVP, currentNode->Point, Point);
  Normalize4(Point);
  for (currentNode = currentNode->Next; currentNode->Type != END; currentNode = currentNode->Next) {
      for (; currentNode->Type == COLOR || currentNode->Type == NORMAL; currentNode = currentNode->Next) {
	switch (currentNode->Type) {
	  case NORMAL:
	    memcpy(currentStack->Normal, currentNode->Normal, sizeof4GLfloat);
	    break;
	  case COLOR:
	    memcpy(currentStack->Color, currentNode->Color, sizeof4GLuint);
	    break;
	  default:
	    break;
	  }
      }
      if (SDL_SetRenderDrawColor(renderer, currentStack->Color[0], currentStack->Color[1], currentStack->Color[2], currentStack->Color[3])) {
	printf("Error en SDL_SetRenderDrawColor en SDL_TR_Lines\n");
	return SDL_FALSE;
      }
      MatrixxPoint4x4(currentStack->MVP, currentNode->Point, Point2);
      printf("x: %d, y: %d\n", (int)Point2[0], (int)Point2[1]);

      Normalize4(Point2);
      //PrintMatrix4x4(currentStack->MVP);
      if (SDL_RenderDrawLine(renderer, (int)Point[0], (int)Point[1], (int)Point2[0], (int)Point2[1])) {
	printf("Error en SDL_RenderDrawLine en SDL_TR_Lines\n");
	return SDL_FALSE;
      }
      memcpy(Point, Point2, sizeof4GLfloat);
    }
  return SDL_TRUE;
}

GLboolean SDL_TR_Line_loop(void)
{
  GLfloat Pointi[4], Point[4], Point2[4];
	
  for (currentNode = currentNode->Next; currentNode->Type == COLOR || currentNode->Type == NORMAL; currentNode = currentNode->Next) {
    switch (currentNode->Type)
      {
      case NORMAL:
	memcpy(currentStack->Normal, currentNode->Normal, sizeof4GLfloat);
	break;
      case COLOR:
	memcpy(currentStack->Color, currentNode->Color, sizeof4GLuint);
	break;
      default:
	break;
      }
  }
  MatrixxPoint4x4(currentStack->MVP, currentNode->Point, Pointi);
  Normalize4(Pointi);
  memcpy(Point, Pointi, sizeof4GLfloat);

  for (currentNode = currentNode->Next; currentNode->Type != END; currentNode = currentNode->Next)
    {
      for (; currentNode->Type == COLOR || currentNode->Type == NORMAL; currentNode = currentNode->Next) {
	switch (currentNode->Type)
	  {
	  case NORMAL:
	    memcpy(currentStack->Normal, currentNode->Normal, sizeof4GLfloat);
	    break;
	  case COLOR:
	    memcpy(currentStack->Color, currentNode->Color, sizeof4GLuint);
	    break;
	  default:
	    break;
	  }
      }
      if (SDL_SetRenderDrawColor(renderer, currentStack->Color[0], currentStack->Color[1], currentStack->Color[2], currentStack->Color[3])) {
	printf("Error en SDL_SetRenderDrawColor en SDL_TR_Lines");
	return SDL_FALSE;
      }
      MatrixxPoint4x4(currentStack->MVP, currentNode->Point, Point2);
      Normalize4(Point2);
      if (SDL_RenderDrawLine(renderer, (int)Point[0], (int)Point[1], (int)Point2[0], (int)Point2[1])) {
	printf("Error en SDL_RenderDrawLine en SDL_TR_Lines");
	return SDL_FALSE;
      }
      memcpy(Point, Point2, sizeof4GLfloat);
    }

  if (SDL_SetRenderDrawColor(renderer, currentStack->Color[0], currentStack->Color[1], currentStack->Color[2], currentStack->Color[3])) {
    printf("Error en SDL_SetRenderDrawColor en SDL_TR_Lines");
    return SDL_FALSE;
  }
  if (SDL_RenderDrawLine(renderer, (int)Point[0], (int)Point[1], (int)Pointi[0], (int)Pointi[1])) {
    printf("Error en SDL_RenderDrawLine en SDL_TR_Lines");
    return SDL_FALSE;
  }
  return SDL_TRUE;
}

GLboolean SDL_TR_Triangles(void)
{
  SDL_TR_Line_loop();

  return SDL_TRUE;
}

GLboolean SDL_TR_Quads(void)
{
  SDL_TR_Line_loop();

  return SDL_TRUE;
}

GLboolean SDL_TR_Poligon(void)
{
  SDL_TR_Line_loop();

  return SDL_TRUE;
}

/* Estas funciones son para cubrir la magia de OpenGL y SDL2 */

GLboolean SDL_TR_CreateRenderer(SDL_Window *_gWindow)
{
  renderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_SOFTWARE); // También podría poner SDL_RENDERER_HARDWARE

  if (renderer == NULL)
    return SDL_FALSE;

  CreateFirstList();

  CreateFirsStack();

  InitMatrix();

  int width, height;
  SDL_GetWindowSize(_gWindow, &width, &height);
  glViewport(0, 0, width, height);

  return SDL_TRUE;
}

void SDL_TR_Quit()
{
  FreeAllLists();
  //FreeStacks();
  SDL_Quit();
}

void InitMatrix(void)
{
  memcpy(firstList->firstNode->Matrix, Identity, sizeof16GLfloat);
}


//#define BEGIN			0x0010
//#define END				0x0011
//
//#define CLEARCOLOR 0xA000
//
//#define LOADIDENTITY 0xA010
//#define LOADMATRIX 0xA011
//#define MULTMATRIX 0xA012
//
//#define MODEL 0xA020
//#define VIEWPORT 0xA021
//#define ORTHO			0xA031
//#define FRUSTUM   0xA032
//
//#define PUSHMATRIX 0xA030
//#define POPMATRIX 0xA031

