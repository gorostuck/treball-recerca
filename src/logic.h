/* Este archivo contiene las declaraciones sobre la l�gica
de la simulaci�n y la gesti�n de eventos */
#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "geometry.h"

int logic_start(void);
int logic_loop(void);

void render_cube(Point P[8]);


#endif // LOGIC_H_INCLUDED
