#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#define SHOWHOST

void show_info(struct utmp *utbufp, char *tty);
void show_time(long timeval);

int main(int argc, char *argv[]) {
  struct utmp *utbufp, *utmp_next();
  char *tty = NULL;

  if (argc == 3) {
    if (strcmp(argv[1], "am") || strcmp(argv[2], "i")) {
      fprintf(stderr, "argument error.");
    } else {
      tty = ttyname(0);
      tty = tty + 5;
    }
  }

  if (utmp_open(UTMP_FILE) == -1) {
    perror(UTMP_FILE);
    exit(EXIT_FAILURE);
  }

  while ((utbufp = utmp_next()) != ((struct utmp *)NULL))
    show_info(utbufp, tty);

  utmp_close();
  return 0;
}  // main

void show_info(struct utmp *utbufp, char *tty) {
  if (utbufp->ut_type != USER_PROCESS)
    return;
  if (tty != NULL && strcmp(tty, utbufp->ut_line))
    return;
  printf("% -8.8s", utbufp->ut_name);
  printf(" ");
  printf("% -8.8s", utbufp->ut_line);
  printf(" ");
  show_time(utbufp->ut_time);
  printf(" ");
#ifdef SHOWHOST
  if (utbufp->ut_host[0] != '\0')
    printf(" (%s)", utbufp->ut_host);
#endif
  printf("\n");
}

void show_time(long timeval) {
  char *cp;
  cp = ctime(&timeval);

  printf("%12.12s", cp+4);
}
