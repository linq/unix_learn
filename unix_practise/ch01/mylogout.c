#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <utmp.h>
#include <string.h>
#include <time.h>

extern int UTMP_SIZE;
extern int utmp_open();
extern void utmp_close();
extern int utmp_seek();
extern struct utmp *utmp_next();

int logout_tty(char *line) {
  struct utmp *rec;
  int retval = EXIT_FAILURE;

  if (utmp_open(UTMP_FILENAME) == -1) {
    fprintf(stderr, "open file %s error", UTMP_FILENAME);
    return retval;
  }

  while ((rec = utmp_next()) != ((struct utmp *)NULL)) {
    if (strncmp(rec->ut_line, line, sizeof(rec->ut_line)) == 0) {
      rec->ut_type = DEAD_PROCESS;
      if (time(&rec->ut_time) != -1) {
        int offset = 1;
        int fd_utmp = utmp_seek(offset, SEEK_CUR);
        if (write(fd_utmp, rec, offset*UTMP_SIZE) == offset*UTMP_SIZE)
          retval = EXIT_SUCCESS;
      }
        retval = utmp_seek(1, SEEK_CUR);
      break;
    }
  }

  utmp_close();

  return retval;
}  // logout_tty

int  main(int argc, char *argv[]) {
  char *name;
  if (argc < 2)
    name = ttyname(0) + 5;
  else
    name = argv[1];

  int ret = logout_tty(name);
  if (ret == EXIT_SUCCESS)
    printf("logout success\n");
  else
    printf("failed\n");

  return 0;
}  // main
