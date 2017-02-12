#include <stdio.h>

#include "window.h"

int main(int argc, char* argv[]) {

  if (start_screen())
    return 1;

  wait_screen(3000);

  end_screen();

  return 0;
}
