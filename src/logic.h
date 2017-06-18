/* Este archivo contiene las declaraciones sobre la lógica
de la simulación y la gestión de eventos */
#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "geometry.h"

int logic_start(void);
int logic_loop(void);

void render_cube(Point P[8]);


#endif // LOGIC_H_INCLUDED
