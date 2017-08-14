#pragma once
#ifndef INITWINDOW_H_INCLUDED
#define INITWINDOW_H_INCLUDED

#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


SDL_bool quit;

void handleKeys(unsigned char key, int x, int y);

static int SCREEN_WIDTH = 640;
static int SCREEN_HEIGHT = 640;

extern struct Node *firstNode, *currentNode;// , *temp;

//The window we'll be rendering to
static SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

extern const GLfloat Identity[16];

//Main loop flag
//SDL_bool quit = SDL_FALSE;

//Starts up SDL, creates window, and initializes OpenGL
int init_window(void);

//Initializes matrices and clear color
int initGL();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
//void update();

//Frees media and shuts down SDL
void close_window();

GLboolean SDL_TR_SwapWindow(void);
//void SDL_TR_SwapWindow(SDL_Window *_gWindow);


#endif // INITWINDOW_H_INCLUDED
