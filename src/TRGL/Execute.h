#pragma once
#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

extern SDL_Renderer *renderer; //Definido en InitWindow.c

GLboolean SDL_TR_Lines(void);
GLboolean SDL_TR_Line_loop(void);
GLboolean SDL_TR_Triangles(void);
GLboolean SDL_TR_Quads(void);
GLboolean SDL_TR_Poligon(void);

void InitMatrix();


#endif // EXECUTE_H_INCLUDED
