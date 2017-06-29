/* Este archivo contiene las declaraciones sobre la lógica de la simulación y la gestión de eventos */
#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#define DEFAULT_MAX_SCREEN_X 512
#define DEFAULT_MAX_SCREEN_Y 512

int logic_start(void);
int logic_loop(void);


/* Esto solía ser screen.h, pero ahora ya no es relevante ya que necesito comunicación con SDL en logic */

int window_start(void);
void window_end(void);
void window_update_size(void);
void set_viewport(int width, int height);

#endif /* LOGIC_H_INCLUDED */
