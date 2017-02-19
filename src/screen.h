/* Este archivo contiene las declaraciones sobre diversos
   aspectos de la ventana y la gestion de eventos */
#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLDUED

#include <SDL2/SDL.h>
#include <stdio.h>

/* Variables sobre la ventana y otros */
#define MAX_SCREEN_X 512
#define MAX_SCREEN_Y 512

int start_screen(void);
int end_screen(void);
void draw_screen(); // Provisional
void wait_screen(int time);

#endif // SCREEN_H_INCLUDED
