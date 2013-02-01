#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 100

int  main(int argc, char *argv[]) {
  int fd;
  char *string = "hello, word!";
  int len = strlen(string);

  if (argc < 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fd = open(argv[1],O_RDWR)) == -1) {
    perror("open file error\n");
    exit(EXIT_FAILURE);
  }

  if(lseek(fd, OFFSET, SEEK_END) == -1) {
    perror("seek file error.");
    exit(EXIT_FAILURE);
  }  

  if (write(fd, string, len) != len) {
    perror("write file error");
  }

  close(fd);

  return 0;
}  // main
