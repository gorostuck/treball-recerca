#pragma once
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <math.h>



#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


#include "Init.h"
#include "Renderer.h"

#ifdef TRGL_MODE
#include "TRGL/Scanner.h"
#include "TRGL/Execute.h"
#endif /* TRGL_MODE */

//#define SCREEN_WIDTH   640
//#define SCREEN_HEIGHT  640

const GLfloat FOV_Y = 60.0f;
const GLfloat NEAR_PLANE = 1.0f;
const GLfloat FAR_PLANE = 100.0f;
const GLfloat CAMERA_ANGLE_X = 45.0f;     // pitch in degree
const GLfloat CAMERA_ANGLE_Y = -45.0f;    // heading in degree
const GLfloat CAMERA_DISTANCE = 25.0f;    // camera distance
																					// default projection matrix values
const GLfloat DEFAULT_LEFT = -0.5f;
const GLfloat DEFAULT_RIGHT = 0.5f;
const GLfloat DEFAULT_BOTTOM = -0.5f;
const GLfloat DEFAULT_TOP = 0.5f;
const GLfloat DEFAULT_NEAR = 1.0f;
const GLfloat DEFAULT_FAR = 10.0f;

#define PI 3.14159265358979323846264338327

#endif // MAIN_H_INCLUDED
