/* Este archivo contiene las declaraciones sobre diversos
   aspectos de la ventana y la gestion de eventos */
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLDUED

#include <SDL2/SDL.h>
#include <stdio.h>

int start_screen(SDL_Window *window);
int end_screen(SDL_Window *window);
void wait_screen(int time);

#endif
