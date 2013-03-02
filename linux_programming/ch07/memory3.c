#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ONE_K (1024)

int main(int argc, const char *argv[])
{
  char *some_memory;
  int size_to_allocate = ONE_K;
  int megs_obtained = 0;
  int ks_obtained = 0;

  while (1) {
    for (ks_obtained = 0; ks_obtained < 1024; ks_obtained++) {
      some_memory = (char *)malloc(size_to_allocate);
      if (some_memory == NULL)
        exit(EXIT_FAILURE);
      sprintf(some_memory, "Hello World");
    }
    megs_obtained++;
    printf("Now allocated %d Metabytes\n", megs_obtained);
  }
  return 0;
}

