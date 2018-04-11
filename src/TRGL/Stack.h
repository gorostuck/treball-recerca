#pragma once
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct Stack {
  GLfloat Normal[4];
  GLuint Color[4];

  GLfloat Model[16];
  GLfloat View[16];
  GLfloat Projection[16];
  GLfloat Viewport[16];

  GLfloat MVP[16];

  GLfloat NormalMatrix[16];

  struct Stack *Next;
};

struct Stack *firstStack, *currentStack;

GLboolean CreateFirsStack(void);
GLboolean CreateStack(void);

void FreeStacks(void);

#endif // STACK_H_INCLUDED
