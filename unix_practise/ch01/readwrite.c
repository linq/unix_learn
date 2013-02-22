#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 20

int  main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "at least two arguments");
    exit(EXIT_FAILURE);
  }
  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[1], O_WRONLY);
  int fd3 = open(argv[1], O_RDONLY);

  if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
    perror("open file error");
    exit(EXIT_FAILURE);
  }

  int reads;
  char buf[BUFFSIZE + 1];
  reads = read(fd1, buf, BUFFSIZE);
  reads = reads >= BUFFSIZE ? BUFFSIZE : reads;
  buf[BUFFSIZE] = '\0';
  printf("in fd1, contents: %s\n", buf);

  char *string = "testing 123 ...";
  size_t len = strlen(string);
  if (write(fd2, string, len) != len)
    perror("write error...");

  reads = read(fd3, buf, BUFFSIZE);
  reads = reads >= BUFFSIZE ? BUFFSIZE : reads;
  buf[BUFFSIZE] = '\0';
  printf("in fd3, contents: %s\n", buf);

  close(fd1);
  close(fd2);
  close(fd3);

  return 0;
}  // main
