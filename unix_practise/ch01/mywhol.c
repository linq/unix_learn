#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "utmplib.h"

void show_utmp(struct utmp *);
void show_time(long);
void show_exit_status(struct exit_status *);
void show_ut_session(struct utmp *);

int  main(int argc, char *argv[]) {
  char *filename = UTMP_FILENAME;
  struct utmp *utmpbuf; 

  if (argc > 1) {
    filename = argv[argc - 1];
  }

  if(utmp_open(filename) == -1) {
    fprintf(stderr, "open file %s error\n", filename);
    exit(EXIT_FAILURE);
  }

  while ((utmpbuf = utmp_next()) != NULLUT) {
    show_utmp(utmpbuf);
  }

  utmp_close();

  return 0;
}  // main

void show_utmp(struct utmp * utp) {
  printf("%8d", utp->ut_type);
  printf(" ");
  printf("%d", utp->ut_pid);
  printf(" ");
  printf("%-8.8s", utp->ut_name);
  printf(" ");
  printf("%-8.8s", utp->ut_line);
  printf(" ");
  printf("%-8.8s", utp->ut_id);
  printf(" ");
  printf("%-8.8s", utp->ut_user);
  printf(" ");
  show_exit_status(&utp->ut_exit);
  show_ut_session(utp);
  printf("%8d", *utp->ut_addr_v6);
  printf(" ");
  show_time(utp->ut_time);
  printf(" ");
  if (utp->ut_host[0] != '\0')
    printf(" (%s)", utp->ut_host);
  printf("\n");
}

void show_time(long timeval) {
  char *cp;
  cp = ctime(&timeval);

  printf("%12.12s", cp+4);
}

void show_exit_status(struct exit_status *stap) {
  printf("(exit status: %4d %4d)", stap->e_termination, stap->e_exit);
  printf(" ");
}

void show_ut_session(struct utmp * utp) {
  printf("%8ld", utp->ut_session);
  printf(" ");
}
