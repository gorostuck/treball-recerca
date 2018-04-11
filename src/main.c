#include "main.h"

int main(int argc, char* argv[])
{
  // Iniciar SDL y crear ventana
  if (!init_window()) {
    printf("Fallo de inicializacion!\n");
  } else {
    // Gestor de eventos
    SDL_Event e;
    
    // Permitir input de texto
    SDL_StartTextInput();
    
    // Detener la aplicación durante la ejecución
    while (!quit) {
      // Gestionar los eventos
      while (SDL_PollEvent(&e) != 0) {
	// Si se intenta cerrar la aplicación
	if (e.type == SDL_QUIT) {
	  quit = SDL_TRUE;
	}
	// Gestionar los inputs de teclas y la posición del ratón
	else if (e.type == SDL_TEXTINPUT) {
	  int x = 0, y = 0;
	  SDL_GetMouseState(&x, &y);
	  handleKeys(e.text.text[0], x, y);
	}
      }

      // Lógica
      if (level == 4 && time > 300.f) time = 0;

      // Renderizar 
      render(level, time);


      time += 1.f;
      
      // Actualizar ventana
      swap_window();
      SDL_Delay(20);
    }
    // Desactivar el input de textos
    SDL_StopTextInput();
  }
  
  // Liberar los recursos y cerrar SDL2
  close_window();
  return 0;
}
