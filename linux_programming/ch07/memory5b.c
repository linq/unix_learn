#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
  char z = *(const char *)0;
  printf("I read from location zero\n");
  return 0;
}
