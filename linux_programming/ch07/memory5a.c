#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
  char *some_memory = (char *)0;

  printf("A read from null %s\n", some_memory);
  sprintf(some_memory, "A write to null\n");
  return 0;
}
