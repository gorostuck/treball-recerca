#pragma once
#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL_opengl.h>

#include "Node.h"
#include "Operation.h"

#define DEG2RAD 0.01745329251 // PI / 180
#define RAD2DEG 57.2957795131 // 180 / PI

extern SDL_Renderer *renderer; //Definido en InitWindow.c
extern struct Node *first, *current;// , *temp; //Definido en Node.h

GLfloat Model[16]; // Matriz movimientos acumulados
GLfloat PushModel[16]; // Matriz movimientos acumulados

GLfloat Translate[16]; // Matriz translación
GLfloat Rotate[16]; // Matriz rotación
GLfloat Scale[16]; // Matriz escalado

GLfloat *MatrixMode;


const GLfloat Identity[16] = { 1.f, 0.f, 0.f, 0.f,
															 0.f, 1.f, 0.f, 0.f,
															 0.f, 0.f, 1.f, 0.f,
															 0.f, 0.f, 0.f, 1.f };

GLAPI void GLAPIENTRY glMultSolf(void);
//GLAPI void GLAPIENTRY ModelxTransformation(void);

#endif // MODEL_H_INCLUDED
