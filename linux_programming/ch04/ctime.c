#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  time_t timeval;

  time(&timeval);
  printf("The date is: %s\n", ctime(&timeval));

  return 0;
}
