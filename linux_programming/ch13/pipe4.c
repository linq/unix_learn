#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
  int data_processed;
  char buffer[BUFSIZ + 1];
  int file_descriptor;

  memset(buffer, sizeof(char), strlen(buffer));
  sscanf(argv[1], "%d", &file_descriptor);
  data_processed = read(file_descriptor, buffer, BUFSIZ);

  printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
  exit(EXIT_SUCCESS);
}
