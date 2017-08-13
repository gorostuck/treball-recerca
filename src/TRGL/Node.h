#pragma once
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "List.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//#include <stdio.h>
//#include <stdlib.h>

#define BEGIN			0x0010
#define END				0x0011

#define CLEARCOLOR 0x4000

#define NORMAL 0x4005
#define COLOR 0x4006

#define LOADIDENTITY 0x4010
#define LOADMATRIX 0x4011
#define MULTMATRIX 0x4012

#define MODEL 0x4020
#define VIEWPORT 0x4021
#define ORTHO			0x4022
#define FRUSTUM   0x4023

#define PUSHMATRIX 0x4030
#define POPMATRIX 0x4031

#define BEGINLIST 0X4040
#define ENDLIST 0X4041
#define LIST 0X4042

#define EXECUTE 0xA050


struct Node {
	GLenum Type;
	GLboolean Visible;

	union{
		union {
			GLfloat Point[4];
			GLfloat Normal[4];
			GLuint Color[4];
		};
		GLfloat Matrix[16];
	};

	struct Node *Next;

	struct List *nextList;

};

//struct Node {
//	GLenum Type;
//	GLboolean Visible;
//
//	GLfloat Point[4];
//	GLfloat Normal[4];
//	GLuint Color[4];
//
//	GLfloat Matrix[16];
//
//	struct Node *Next;
//
//	struct List *nextList;
//
//};

GLboolean CreateFirstNode(struct Node **node);
GLboolean CreateNode(struct Node **node, GLenum type);
//GLboolean CreateNode(GLenum mode);

void FreeNodes(struct Node *node);
//void FreeNodes(struct Node **node);

#endif // NODE_H_INCLUDED
