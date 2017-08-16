#pragma once
#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL_opengl.h>

void Multiplicacion4x4(GLfloat *A, GLfloat *B, GLfloat *C);
void Multiplicacion24x4(GLfloat *A, GLfloat *B, GLfloat *C, GLfloat *D);

void Inverse4x4(GLfloat *m, GLfloat *mi);

void MatrixxPoint4x4(GLfloat *Matrix, GLfloat *Point, GLfloat *Point2);

void VectorxMatrix4x4(GLfloat *Vector, GLfloat *Matrix, GLfloat *Vector2);

void Normalize4(GLfloat *Point);

void PrintMatrix4x4(GLfloat *Matrix);

#endif // OPERATION_H_INCLUDED
