#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  FILE *f;

  f = fopen("not_here", "r");
  if (!f)
    syslog(LOG_ERR|LOG_USER, "oops - %m\n");
  return 0;
}
