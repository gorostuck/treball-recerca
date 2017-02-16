#include <stdio.h>

#include "window.h"

int main(int argc, char* argv[]) {

  SDL_Window *main_window = NULL;

  if (start_screen(main_window))
    return 1;

  wait_screen(3000);

  end_screen(main_window);

  SDL_Quit();

  return 0;
}
