#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int argc, char *argv[]) {
  bool interactive = false, override = false;
  int in_fd, out_fd, n_chars;
  char *source = NULL, *dest = NULL;
  char buf[BUFFSIZE];

  if (argc < 3) {
    fprintf(stderr, "usage: %s source destination\n", *argv);
    exit(EXIT_FAILURE);
  }

  int i;
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'i') {
        interactive = true;
        break;
      }
    } else {
      if (source == NULL) {
        source = argv[i];
        if (argv[i+1][0] == '-') {
          fprintf(stderr, "usage: %s source destination\n", *argv);
          exit(EXIT_FAILURE);
        } else {
          dest = argv[i+1];
        }
      }
    }
  }

  if (!strcmp(source, dest)) {
    fprintf(stderr, "%s: %s and %s are the same file\n", argv[0], source, dest);
    exit(EXIT_FAILURE);
  }

  if (interactive) {
    printf("%s: override '%s'?\n", argv[0], dest);
    char answer[4];
    scanf("%s", answer);
    if (strstr(answer, "yes") || strpbrk(answer, "yY\n"))
      override = true;
    else
      return 0;
  }

  if ((in_fd = open(source, O_RDONLY)) == -1)
    oops("Cannot open", source);

  if ((out_fd = creat(dest, COPYMODE)) == -1)
    oops("Cannot create", dest);

  while ((n_chars = read(in_fd, buf, BUFFSIZE)) > 0) {
    if (write(out_fd, buf, n_chars) != n_chars)
      oops("Write error to ", dest);
  }

  if (n_chars == -1)
    oops("Read error from ", source);

  if (close(in_fd) == -1 || close(out_fd) == -1)
    oops("Error closing files", "");

  return 0;
}  // main

void oops(char *s1, char *s2) {
  fprintf(stderr, "Error: %s", s1);
  perror(s2);
  exit(EXIT_FAILURE);
}
