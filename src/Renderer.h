#pragma once
#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Objects.h"
#include "Examples.h"

static SDL_bool gRenderQuad = SDL_TRUE;

void render(void);

#endif // RENDERER_H_INCLUDED
