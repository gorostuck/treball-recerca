/* Este archivo contiene las declaraciones sobre diversos
   aspectos de la ventana y la gestion de eventos */
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window *window;
int start_screen();
int end_screen();
void wait_screen(int time);

#endif
