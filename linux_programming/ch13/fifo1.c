#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
  int res = mkfifo("/tmp/my_info", 0777);
  if (res == 0)
    printf("FIFO created\n");
  exit(EXIT_SUCCESS);
}
