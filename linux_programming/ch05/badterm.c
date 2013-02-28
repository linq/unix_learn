#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  setupterm("unlist", fileno(stdout), (int *)0);
  printf("Done.\n");

  return 0;
}
