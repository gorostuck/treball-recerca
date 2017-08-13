#pragma once

#include "Node.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct List {
	GLuint Index;

	GLenum modeList;

	struct Node *firstNode, *currentNode;

	struct List *Prev, *Next; //Unir toda las listas
};

//GLuint indexList = -1;

GLboolean CreateFirstList(void);

GLuint CreateList(GLuint item);

GLuint CreateLists(GLsizei range);

struct List *pointerList(GLuint list);

void FreeFirstList(void);
	
void FreeList(GLushort index);

void FreeAllLists(void);
