#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 8

int main(int argc, const char *argv[])
{
  struct termios initialrsetting, newrsettings;
  char password[PASSWORD_LEN + 1];
  tcgetattr(fileno(stdin), &initialrsetting);
  newrsettings = initialrsetting;
  newrsettings.c_lflag &= ~ECHO;

  printf("Enter password: \n");
  if (tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
    fprintf(stderr, "Could not set attributes\n");
  } else {
    fgets(password, PASSWORD_LEN, stdin);
    tcsetattr(fileno(stdin), TCSANOW, &initialrsetting);
    fprintf(stdout, "\nYou entered %s\n", password);
  }

  return 0;
}
