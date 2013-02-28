#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  int nrows, ncolumns;

  setupterm(NULL, fileno(stdin), (int *)0);
  nrows = tigetnum("lines");
  ncolumns = tigetnum("cols");
  printf("This terminal has %d columns and %d rows\n", ncolumns, nrows);

  return 0;
}
