#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  SDL_Window *my_window;

  SDL_Init(SDL_INIT_VIDEO);

  // Open window
  my_window = SDL_CreateWindow("TEST",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               512,
                               512,
                               SDL_WINDOW_OPENGL);

  // Check window's init
  if (my_window == NULL) {
    printf("No s'ha pogut crear la finestra: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Delay(3000);

  SDL_DestroyWindow(my_window);

  SDL_Quit();
  return 0;
}
