#pragma once
#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL_opengl.h>

#include "Node.h"
#include "List.h"
#include "Scanner.h"

extern SDL_Renderer *renderer; //Definido en InitWindow.c
//extern struct Node *first, *current;// , *temp; //Definido en Node.h

GLboolean SDL_TR_Lines(void);
GLboolean SDL_TR_Line_loop(void);
GLboolean SDL_TR_Triangles(void);
GLboolean SDL_TR_Quads(void);
GLboolean SDL_TR_Poligon(void);
GLboolean SDL_TR_CreateRenderer(SDL_Window *gWindow);

void SDL_TR_Quit();
void InitMatrix();


#endif // EXECUTE_H_INCLUDED
