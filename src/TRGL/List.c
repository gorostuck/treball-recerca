#include "List.h"

#include <stdio.h>
#include <stdlib.h>

struct List *firstList = NULL, *currentList = NULL;

GLuint indexList = -1;

GLboolean CreateFirstList(void)
{
  firstList = (struct List *)malloc(sizeof(struct List));
  if (firstList == NULL)
    return GL_FALSE;

  firstList->Prev = NULL;
  firstList->Next = NULL;

  firstList->Index = indexList = 0;

  CreateFirstNode(&(firstList->firstNode));
  firstList->currentNode = firstList->firstNode;
  currentList = firstList;

  //printf("%i  %p\n", mode, current);
  return GL_TRUE;
}

GLuint CreateList(GLuint item)
{
  struct List *tempList;

  tempList = (struct List *)malloc(sizeof(struct List));
  if (tempList == NULL)
    return GL_FALSE;

  tempList->Prev = firstList;
  tempList->Next = firstList->Next;
  firstList->Next = tempList;

  tempList->Index = item;
	
  CreateNode(&(tempList->firstNode), BEGIN);
  tempList->currentNode = tempList->firstNode;

  //printf("%i  %p\n", mode, current);
  return GL_TRUE;
}

GLuint CreateLists(GLsizei range)
{
  GLuint i ;

  indexList++;
  for (i = indexList; i < indexList + (GLuint)range; i++) {
    CreateList( i );
  }
  indexList += (GLuint)range - 1;

  return indexList - (GLuint)range;
}

struct List *pointerList(GLuint list)
{
  struct List *tempList;

  for (tempList = firstList->Next; tempList->Index != list || tempList == NULL; tempList = tempList->Next);

  return tempList;
}

void FreeFirstList(void)
{
  FreeNodes(firstList->firstNode->Next);
  firstList->firstNode->Next = NULL;
  firstList->currentNode = firstList->firstNode;
}

void FreeList(GLushort index)
{
  struct List *tempList;

  for (tempList = firstList->Next; tempList->Index != index || tempList == NULL; tempList = tempList->Next);

  FreeNodes(tempList->firstNode);

  free(tempList);
  tempList = NULL;
}

void FreeAllLists(void)
{
  struct List *tempList, *tempList2;

  for (tempList = firstList->Next; tempList != NULL; tempList = tempList2){
    FreeNodes(tempList->firstNode);

    tempList2 = tempList->Next;
    free(tempList);
    tempList = NULL;
  }
  free(firstList->firstNode);	firstList->firstNode = NULL;
  free(firstList); firstList = NULL;
}
