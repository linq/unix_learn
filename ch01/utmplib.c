#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include <unistd.h>
#include "utmplib.h"

const int UTMP_SIZE = sizeof(struct utmp);
static char utmpbuf[NRECS * UTSIZE];
static int num_rect;
static int cur_rec;
static int fd_utmp = -1;

int utmp_open(char *filename) {
  fd_utmp = open(filename, O_RDONLY);
  cur_rec = num_rect = 0;
  return fd_utmp;
}

int utmp_reload() {
  int amt_read;
  amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
  num_rect = amt_read / UTSIZE;
  cur_rec = 0;

  return num_rect;
}

struct utmp *utmp_next() {
  struct utmp *recp = NULL;
  if (fd_utmp == -1)
    return NULLUT;
  while (recp == NULL || recp->ut_host == NULL || recp->ut_line == NULL || recp->ut_name == NULL) {
    if (cur_rec == num_rect && utmp_reload() == 0)
      return NULLUT;
    recp = (struct utmp *)&utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
  }
  return recp;
}

int utmp_seek(off_t offset, int whence) {
  lseek(fd_utmp, -offset*UTMP_SIZE, whence);
  return fd_utmp;
}

void utmp_close() {
  if (fd_utmp != -1)
    close(fd_utmp);
}
