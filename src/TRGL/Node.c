#include "Node.h"

#include <stdio.h>
#include <stdlib.h>

GLboolean CreateFirstNode(struct Node **node)
{
  *node = (struct Node *)malloc(sizeof(struct Node));
  if (*node == NULL)
    return GL_FALSE;

  (*node)->Type = BEGIN;

  (*node)->Next = NULL;

  //printf("First Nodde %p\n", *node);

  return GL_TRUE;
}

GLboolean CreateNode(struct Node **node, GLenum type)
{
  (*node) = (*node)->Next = (struct Node *)malloc(sizeof(struct Node));
  if (*node == NULL)
    return GL_FALSE;

  (*node)->Type = type;

  (*node)->Next = NULL;

  //printf("%i  %p\n",type, *node);

  return GL_TRUE;
}

void FreeNodes(struct Node *node)
{
  struct Node *tempNode;

  for (; node != NULL; node = tempNode) {
    tempNode = node->Next;
    free(node);
    node = NULL;
  }
}
