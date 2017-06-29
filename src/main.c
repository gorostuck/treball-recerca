#include <stdio.h>

#define TRGL_MODE

#include "logic.h"
int main(int argc, char *argv[])
{
  if (logic_start())
    return 1;
  return 0;
}
