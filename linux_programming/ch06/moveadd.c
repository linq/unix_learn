#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

int main(int argc, const char *argv[])
{
  const char witch_one[] = " First Witch ";
  const char witch_two[] = " Second Witch ";
  const char *scan_ptr;

  initscr();

  move(5, 15);
  attron(A_BOLD);
  printw("%s", "Macbeth");
  attroff(A_BOLD);
  refresh();
  sleep(1);

  move(8, 15);
  attron(A_STANDOUT);
  printw("%s", "Thunder and Lightning");
  attroff(A_STANDOUT);
  refresh();
  sleep(1);

  move(10, 10);
  printw("%s", "When shall we three meet again");
  move(11, 23);
  printw("%s", "In thunder, lighning, or in rain");
  move(13, 10);
  printw("%s", "When the hurlyburly' done");
  move(14, 23);
  printw("%s", "When the battle' lost and won.");
  refresh();
  sleep(1);

  attron(A_DIM);
  scan_ptr = witch_one + strlen(witch_one) - 1;
  while (scan_ptr != witch_one) {
    move(10, 10);
    insch(*scan_ptr--);
  }
  attroff(A_DIM);

  refresh();
  sleep(1);

  move(LINES -1 , COLS-1);
  refresh();
  sleep(1);

  endwin();
  return 0;
}
