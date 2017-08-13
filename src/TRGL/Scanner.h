#pragma once
#ifndef SCANER_H_INCLUDED
#define SCANER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Node.h"
#include "List.h"
#include "Stack.h"
#include "Matrix.h"

#define DEG2RAD 0.01745329251f // PI / 180
#define RAD2DEG 57.2957795131f // 180 / PI

//GLenum Execute;

void SDL_TR_Perspective(GLfloat fovY, GLfloat aspect, GLfloat front, GLfloat back);

GLAPI void GLAPIENTRY glMatrixMode(GLenum flags);

void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
	GLdouble centerx, GLdouble centery, GLdouble centerz,
	GLdouble upx, GLdouble upy, GLdouble upz);


#endif // SCANER_H_INCLUDED