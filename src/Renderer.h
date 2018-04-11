#pragma once
#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define DEG2RAD 0.01745329251f // PI / 180
#define RAD2DEG 57.2957795131f // 180 / PI

#include "Objects.h"
#include "Examples.h"

static SDL_bool gRenderQuad = SDL_TRUE;

void render(GLint level, GLfloat time);

void gluPerspective(GLfloat fovY, GLfloat aspect, GLfloat front, GLfloat back);
void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
	       GLdouble centerx, GLdouble centery, GLdouble centerz,
	       GLdouble upx, GLdouble upy, GLdouble upz);

#endif // RENDERER_H_INCLUDED
