#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack *firstStack = NULL, *currentStack;// , *currentStack = NULL;

const GLfloat Identity[16] = { 1.f, 0.f, 0.f, 0.f,
			       0.f, 1.f, 0.f, 0.f,
			       0.f, 0.f, 1.f, 0.f,
			       0.f, 0.f, 0.f, 1.f };
const GLfloat Vector0[4] = { 0.f, 0.f, 0.f, 0.f };

// Valores definidos en Execute.c
extern const size_t sizeof4GLuint;
extern const size_t sizeof4GLfloat;
extern const size_t sizeof16GLfloat;

GLboolean CreateFirsStack(void)
{
  firstStack = (struct Stack *)malloc(sizeof(struct Stack));
  if (firstStack == NULL)
    return GL_FALSE;

  memcpy(firstStack->Normal, Vector0, sizeof4GLfloat);
  memcpy(firstStack->Color, Vector0, sizeof4GLfloat);

  memcpy(firstStack->Model, Identity, sizeof16GLfloat);
  memcpy(firstStack->View, Identity, sizeof16GLfloat);
  memcpy(firstStack->Projection, Identity, sizeof16GLfloat);
  memcpy(firstStack->Viewport, Identity, sizeof16GLfloat);

  firstStack->Next = NULL;
  currentStack = firstStack;

  return GL_TRUE;
}

GLboolean CreateStack(void)
{
  struct Stack *temp;

  temp = (struct Stack *)malloc(sizeof(struct Stack));
  if (temp == NULL)
    return GL_FALSE;

  temp->Next = firstStack;
  firstStack = temp;

  memcpy(firstStack, firstStack->Next, sizeof(struct Stack));

  //	printf("%i  %p\n", mode, currentStack);

  return GL_TRUE;
}

void FreeStack(void)
{
  struct Stack *temp = firstStack->Next;

  free(firstStack);
  firstStack = temp;
}

void FreeStacks(void)
{
  struct Stack *tempStack;

  for (tempStack = firstStack->Next; firstStack != NULL; firstStack = tempStack) {
    tempStack = firstStack->Next;
    free(firstStack);
  }
}
