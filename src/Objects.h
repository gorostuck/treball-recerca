#pragma once
#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define PI 3.14159265358979323846264338327

void Cubo(GLfloat s);
void CuboNegro(GLfloat s);
void Esfera(void);
void AxisPlane(void);
void Vector(GLfloat size);
void Vector2(GLfloat x, GLfloat y, GLfloat z);


// Presentación
void Cubo0();
void Plano1();
void Cubo1(GLfloat margen);
void Plano2();

#endif // OBJECTS_H_INCLUDED
