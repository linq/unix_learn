#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main(int argc, const char *argv[])
{
  initscr();

  move(5, 15);
  printw("%s", "Hello, world");
  refresh();

  sleep(2);

  endwin();
  return 0;
}
