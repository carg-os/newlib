#include <stdlib.h>

int main();

void _start() {
  asm volatile(".option norelax\n"
               "la gp, __global_pointer$");
  exit(main());
}
